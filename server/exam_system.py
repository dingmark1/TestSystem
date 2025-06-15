import os
from datetime import datetime, timedelta
from flask import Flask, request, jsonify, send_from_directory
from flask_sqlalchemy import SQLAlchemy
import jwt
from functools import wraps
from werkzeug.security import generate_password_hash, check_password_hash
import logging
from sqlalchemy.ext.associationproxy import association_proxy
from flask import g
from sqlalchemy.dialects.postgresql import JSON
from sqlalchemy.exc import SQLAlchemyError

logging.basicConfig(level=logging.DEBUG)

# 初始化Flask应用
app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///exam.db'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
app.config['SECRET_KEY'] = 'your-super-secret-key-12345'
db = SQLAlchemy(app)

# ------------------ 数据库模型 ------------------
class User(db.Model):
    __tablename__ = 'users'
    id = db.Column(db.Integer, primary_key=True)
    sid = db.Column(db.String(20), unique=True)
    username = db.Column(db.String(80), unique=True, nullable=False)
    password_hash = db.Column(db.String(128))
    user_type = db.Column(db.String(20), nullable=False)
    created_at = db.Column(db.DateTime, default=datetime.utcnow)

    # 确保正确定义密码方法
    def set_password(self, password):
        self.password_hash = generate_password_hash(password)  # 使用导入的函数

    def check_password(self, password):
        return check_password_hash(self.password_hash, password)  # 使用导入的函数

class Question(db.Model):
    __tablename__ = 'questions'
    id = db.Column(db.Integer, primary_key=True)
    sid = db.Column(db.String(20), unique=True)
    qtype = db.Column(db.String(20), nullable=False)  # 单选题/多选题/判断题/简答题
    question = db.Column(db.Text, nullable=False)
    options = db.Column(JSON(none_as_null=True))
    answer = db.Column(db.Text)
    subject = db.Column(db.String(50))
    uploader = db.Column(db.String(50))
    created_at = db.Column(db.DateTime, default=datetime.utcnow)
    image_data = db.Column(db.LargeBinary)  # 存储题目相关图片
    uploader_id = db.Column(db.Integer, db.ForeignKey('users.id'))
    papers = db.relationship('PaperQuestion', back_populates='question')

class ExamPaper(db.Model):
    __tablename__ = 'exampapers'
    id = db.Column(db.Integer, primary_key=True)
    sid = db.Column(db.String(20), unique=True)
    name = db.Column(db.String(200), nullable=False)
    creator_id = db.Column(db.Integer, db.ForeignKey('users.id'))
    created_at = db.Column(db.DateTime, default=datetime.utcnow)
    
    paper_questions = db.relationship('PaperQuestion', back_populates='paper')
    questions = association_proxy(
        'paper_questions',
        'question',
        creator=lambda q_score: PaperQuestion(
            question=q_score[0],
            score=q_score[1]
        )
    )
class PaperQuestion(db.Model):
    __tablename__ = 'paper_questions'
    paper_id = db.Column(db.Integer, db.ForeignKey('exampapers.id'), primary_key=True)
    question_id = db.Column(db.Integer, db.ForeignKey('questions.id'), primary_key=True)
    score = db.Column(db.Float)
    
    paper = db.relationship('ExamPaper', back_populates='paper_questions')
    question = db.relationship('Question', back_populates='papers')

class ExamRecord(db.Model):
    __tablename__ = 'exam_records'
    id = db.Column(db.Integer, primary_key=True)
    user_id = db.Column(db.Integer, db.ForeignKey('users.id'))
    paper_id = db.Column(db.Integer, db.ForeignKey('exampapers.id'))
    start_time = db.Column(db.DateTime)
    end_time = db.Column(db.DateTime)
    total_score = db.Column(db.Float)

class ExamAnswer(db.Model):
    __tablename__ = 'exam_answers'
    id = db.Column(db.Integer, primary_key=True)
    record_id = db.Column(db.Integer, db.ForeignKey('exam_records.id'))
    question_id = db.Column(db.Integer, db.ForeignKey('questions.id'))
    user_answer = db.Column(db.Text)
    score = db.Column(db.Float)

class AnswerImage(db.Model):
    __tablename__ = 'answer_images'
    id = db.Column(db.Integer, primary_key=True)
    record_id = db.Column(db.Integer, db.ForeignKey('exam_records.id'))
    image_data = db.Column(db.LargeBinary, nullable=False)
    uploaded_at = db.Column(db.DateTime, default=datetime.utcnow)

# ------------------ 辅助函数 ------------------
def role_required(required_role):
    def decorator(f):
        @wraps(f)
        def wrapper(*args, **kwargs):
            auth_header = request.headers.get("Authorization")
            if not auth_header or not auth_header.startswith("Bearer "):
                return jsonify({"error": "缺少认证令牌"}), 401
                
            token = auth_header.split(" ")[1]
            try:
                payload = jwt.decode(
                    token, 
                    app.config["SECRET_KEY"], 
                    algorithms=["HS256"]
                )
                user = User.query.get(payload["user_id"])
                if not user or user.user_type != required_role:
                    return jsonify({"error": "权限不足"}), 403
                g.current_user = user  # 使用新的参数名避免冲突
                return f(*args, **kwargs)
            except jwt.ExpiredSignatureError:
                return jsonify({"error": "令牌已过期"}), 401
            except Exception as e:
                app.logger.error(f"令牌验证失败: {str(e)}")
                return jsonify({"error": "无效令牌"}), 401
        return wrapper
    return decorator

def get_current_user():
    token = request.headers.get('Authorization', '').split(' ')[-1]
    try:
        payload = jwt.decode(token, app.config['SECRET_KEY'], algorithms=['HS256'])
        return User.query.get(payload['user_id'])
    except:
        return None

def validate_required(data, required_fields):
    missing = [field for field in required_fields if field not in data]
    if missing:
        return False, f"Missing required fields: {', '.join(missing)}"
    return True, ""

# ------------------ 路由定义 ------------------
@app.route('/')
def index():
    return "题库管理系统 API 服务运行中", 200

@app.route('/favicon.ico')
def favicon():
    return send_from_directory(os.path.join(app.root_path, 'static'),
                             'favicon.ico',
                             mimetype='image/vnd.microsoft.icon')

@app.route("/login", methods=["POST"])
def login():

    data = request.get_json()
    if not data or not data['username'] or not data['password']:
        return jsonify({"error": "需要用户名和密码"}), 401
    
    user = User.query.filter_by(username = data['username']).first()
    if not user or not user.check_password(data['password']):
        return jsonify({"error": "无效凭证"}), 401

    """
    # 没做令牌认证
    auth = request.authorization
    if not auth or not auth.username or not auth.password:
        print("111")
        return jsonify({"error": "需要用户名和密码"}), 401

    user = User.query.filter_by(username=auth.username).first()
    if not user or not user.check_password(auth.password):
        print("222")
        return jsonify({"error": "无效凭证"}), 401
    """

    try:
        token = jwt.encode(
            {
                "user_id": user.id,
                "user_type": user.user_type,  # 确保包含角色信息
                "exp": datetime.utcnow() + timedelta(hours=1)
            },
            app.config["SECRET_KEY"],
            algorithm="HS256"
        )
        return jsonify(
            code=200,
            message="Login successful",
            data={
                "token": token,
                'user_id': str(user.id),
                'username': user.username,
                'user_type': user.user_type
            }
        )
    except Exception as e:
        return jsonify({"error": "令牌生成失败"}), 500

def handle_question(q_type):
    try:
        data = request.get_json()
        required = ['question', 'subject', 'uploader']
        
        if q_type in ['单选题', '多选题']:
            required.extend(['options', 'answer'])
        elif q_type == '判断题':
            required.append('answer')
        elif q_type == '简答题':
            required.append('answer')
        
        valid, msg = validate_required(data, required)
        if not valid:
            return jsonify(code=400, message=msg), 400

        new_question = Question(
            qtype = q_type,
            question = data['question'],
            subject = data['subject'],
            uploader = data['uploader'],
            #uploader_id = User.query.filter_by(username = uploader),
            created_at = datetime.utcnow()
        )

        if q_type in ['单选题', '多选题']:
            new_question.options = data['options']
            new_question.answer = data['answer']
        elif q_type == '判断题':
            new_question.answer = data['answer']
        elif q_type == '简答题':
            new_question.answer = data['answer']
        
        db.session.add(new_question)
        db.session.flush()
        new_question.sid = str(new_question.id)
        db.session.commit()
        
        return jsonify(code=200, message="Question added successfully"), 200
    except Exception as e:
        return jsonify(code=500, message=str(e)), 500

@app.route('/add_singleselect', methods=['POST'])
def add_single_select():
    return handle_question('单选题')

@app.route('/add_mulselect', methods=['POST'])
def add_multi_select():
    return handle_question('多选题')

@app.route('/add_judge', methods=['POST'])
def add_judge():
    return handle_question('判断题')

@app.route('/add_shortanswer', methods=['POST'])
def add_short_answer():
    return handle_question('简答题')

@app.route('/query_question', methods=['POST'])
def query_question():
    try:
        data = request.get_json()

        print(data['uploader'])
        if(data['uploader'] == "_ALL_"):
            questions = Question.query.filter_by(subject = data['content']).all()
        else:
            questions = Question.query.filter_by(uploader=data['uploader'], subject = data['content']).all()

        return jsonify(
            code=200,
            message="Success",
            data=[{
                'id': q.sid,
                'question': q.question,
                'subject': q.subject,
                'type': q.qtype
            } for q in questions]
        )
    except Exception as e:
        return jsonify(code=500, message=str(e)), 500

@app.route('/delete_data', methods=['POST'])
def delete_data():
    try:
        data = request.get_json()
        
        # 参数校验增强
        if 'id' not in data or not isinstance(data['id'], str) or not data['id'].strip():
            return jsonify(code=400, message="Invalid or missing question ID"), 400

        # 使用更规范的查询方式
        question = Question.query.filter_by(sid=data['id'].strip()).first()
        
        if not question:
            app.logger.warning(f"Question not found with sid: {data['id']}")
            return jsonify(code=404, message="Question not found"), 404

        # 直接使用已查询到的对象进行删除
        db.session.delete(question)
        db.session.commit()
        
        app.logger.info(f"Deleted question: {data['id']}")
        return jsonify(
            code=200,
            message="Deleted successfully",
            deleted_id=data['id']
        ), 200

    except SQLAlchemyError as e:
        db.session.rollback()
        app.logger.error(f"Database error deleting question: {str(e)}")
        return jsonify(code=500, message="Database operation failed"), 500
    except Exception as e:
        app.logger.critical(f"Unexpected error: {str(e)}", exc_info=True)
        return jsonify(code=500, message="Internal server error"), 500

@app.route('/specific_singlequestion', methods=['POST'])
def get_modify_single():
    try:
        data = request.get_json()
        if 'id' not in data:
            return jsonify(code=400, message="missing question id"), 400
        q = Question.query.filter_by(sid=data['id'].strip()).first()
        if not q:
            app.logger.warning(f"Question not found with id: {data['id']}")
            return jsonify(code=404, message="Question not found"), 404
        app.logger.info(f"get modify question: {data['id']}")
        return jsonify(
            code=200,
            message="Success",
            data={
                'id': q.sid,
                'question': q.question,
                'subject': q.subject,
                'answer': q.answer,
                'options': q.options
            }
        )
    except SQLAlchemyError as e:
        db.session.rollback()
        app.logger.error(f"Database error modifying question: {str(e)}")
        return jsonify(code=500, message="Database operation failed"), 500
    except Exception as e:
        app.logger.critical(f"Unexpected error: {str(e)}", exc_info=True)
        return jsonify(code=500, message="Internal server error"), 500

@app.route('/change_specific_singlequestion', methods=['POST'])
def modify_single():
    try:
        data = request.get_json()
        if 'ID' not in data:
            return jsonify(code=400, message="missing question ID"), 400
        question = Question.query.filter_by(id=data['ID']).first()
        if not question:
            app.logger.warning(f"Question not found with id: {data['ID']}")
            return jsonify(code=404, message="Question not found"), 404
        question.question = data['question']
        question.options = data['options']
        question.answer = data['answer']
        question.subject = data['subject']
        question.uploader = data['uploader']
        db.session.commit()
        app.logger.info(f"Modify question: {data['ID']}")
        return jsonify(
            code=200,
            message="Modify successfully",
        ), 200
    except SQLAlchemyError as e:
        db.session.rollback()
        app.logger.error(f"Database error modifying question: {str(e)}")
        return jsonify(code=500, message="Database operation failed"), 500
    except Exception as e:
        app.logger.critical(f"Unexpected error: {str(e)}", exc_info=True)
        return jsonify(code=500, message="Internal server error"), 500

@app.route('/specific_mulquestion', methods=['POST'])
def get_modify_multi():
    try:
        data = request.get_json()
        if 'id' not in data:
            return jsonify(code=400, message="missing question id"), 400
        q = Question.query.filter_by(sid=data['id'].strip()).first()
        if not q:
            app.logger.warning(f"Question not found with id: {data['id']}")
            return jsonify(code=404, message="Question not found"), 404
        app.logger.info(f"get modify question: {data['id']}")
        return jsonify(
            code=200,
            message="Success",
            data={
                'id': q.sid,
                'question': q.question,
                'subject': q.subject,
                'answer': q.answer,
                'options': q.options
            }
        )
    except SQLAlchemyError as e:
        db.session.rollback()
        app.logger.error(f"Database error modifying question: {str(e)}")
        return jsonify(code=500, message="Database operation failed"), 500
    except Exception as e:
        app.logger.critical(f"Unexpected error: {str(e)}", exc_info=True)
        return jsonify(code=500, message="Internal server error"), 500

@app.route('/change_specific_mulquestion', methods=['POST'])
def modify_multi():
    try:
        data = request.get_json()
        if 'ID' not in data:
            return jsonify(code=400, message="missing question ID"), 400
        question = Question.query.filter_by(id=data['ID']).first()
        if not question:
            app.logger.warning(f"Question not found with id: {data['ID']}")
            return jsonify(code=404, message="Question not found"), 404
        question.question = data['question']
        question.options = data['options']
        question.answer = data['answer']
        question.subject = data['subject']
        question.uploader = data['uploader']
        db.session.commit()
        app.logger.info(f"Modify question: {data['ID']}")
        return jsonify(
            code=200,
            message="Modify successfully",
        ), 200
    except SQLAlchemyError as e:
        db.session.rollback()
        app.logger.error(f"Database error modifying question: {str(e)}")
        return jsonify(code=500, message="Database operation failed"), 500
    except Exception as e:
        app.logger.critical(f"Unexpected error: {str(e)}", exc_info=True)
        return jsonify(code=500, message="Internal server error"), 500

@app.route('/specific_judgequestion', methods=['POST'])
def get_modify_judge():
    try:
        data = request.get_json()
        if 'id' not in data:
            return jsonify(code=400, message="missing question id"), 400
        q = Question.query.filter_by(sid=data['id'].strip()).first()
        if not q:
            app.logger.warning(f"Question not found with id: {data['id']}")
            return jsonify(code=404, message="Question not found"), 404
        app.logger.info(f"get modify question: {data['id']}")
        return jsonify(
            code=200,
            message="Success",
            data={
                'id': q.sid,
                'question': q.question,
                'subject': q.subject,
                'answer': q.answer
            }
        )
    except SQLAlchemyError as e:
        db.session.rollback()
        app.logger.error(f"Database error modifying question: {str(e)}")
        return jsonify(code=500, message="Database operation failed"), 500
    except Exception as e:
        app.logger.critical(f"Unexpected error: {str(e)}", exc_info=True)
        return jsonify(code=500, message="Internal server error"), 500

@app.route('/change_specific_judgequestion', methods=['POST'])
def modify_judge():
    try:
        data = request.get_json()
        if 'ID' not in data:
            return jsonify(code=400, message="missing question ID"), 400
        question = Question.query.filter_by(id=data['ID']).first()
        if not question:
            app.logger.warning(f"Question not found with id: {data['ID']}")
            return jsonify(code=404, message="Question not found"), 404
        question.question = data['question']
        question.answer = data['answer']
        question.subject = data['subject']
        question.uploader = data['uploader']
        db.session.commit()
        app.logger.info(f"Modify question: {data['ID']}")
        return jsonify(
            code=200,
            message="Modify successfully",
        ), 200
    except SQLAlchemyError as e:
        db.session.rollback()
        app.logger.error(f"Database error modifying question: {str(e)}")
        return jsonify(code=500, message="Database operation failed"), 500
    except Exception as e:
        app.logger.critical(f"Unexpected error: {str(e)}", exc_info=True)
        return jsonify(code=500, message="Internal server error"), 500

@app.route('/specific_shortquestion', methods=['POST'])
def get_modify_short():
    try:
        data = request.get_json()
        if 'id' not in data:
            return jsonify(code=400, message="missing question id"), 400
        q = Question.query.filter_by(sid=data['id'].strip()).first()
        if not q:
            app.logger.warning(f"Question not found with id: {data['id']}")
            return jsonify(code=404, message="Question not found"), 404
        app.logger.info(f"get modify question: {data['id']}")
        return jsonify(
            code=200,
            message="Success",
            data={
                'id': q.sid,
                'question': q.question,
                'subject': q.subject,
                'answer': q.answer,
            }
        )
    except SQLAlchemyError as e:
        db.session.rollback()
        app.logger.error(f"Database error modifying question: {str(e)}")
        return jsonify(code=500, message="Database operation failed"), 500
    except Exception as e:
        app.logger.critical(f"Unexpected error: {str(e)}", exc_info=True)
        return jsonify(code=500, message="Internal server error"), 500

@app.route('/change_specific_shortquestion', methods=['POST'])
def modify_short():
    try:
        data = request.get_json()
        if 'ID' not in data:
            return jsonify(code=400, message="missing question ID"), 400
        question = Question.query.filter_by(id=data['ID']).first()
        if not question:
            app.logger.warning(f"Question not found with id: {data['ID']}")
            return jsonify(code=404, message="Question not found"), 404
        question.question = data['question']
        question.answer = data['answer']
        question.subject = data['subject']
        question.uploader = data['uploader']
        db.session.commit()
        app.logger.info(f"Modify question: {data['ID']}")
        return jsonify(
            code=200,
            message="Modify successfully",
        ), 200
    except SQLAlchemyError as e:
        db.session.rollback()
        app.logger.error(f"Database error modifying question: {str(e)}")
        return jsonify(code=500, message="Database operation failed"), 500
    except Exception as e:
        app.logger.critical(f"Unexpected error: {str(e)}", exc_info=True)
        return jsonify(code=500, message="Internal server error"), 500

@app.route('/query_user', methods=['POST'])
def query_user():
    try:
        data = request.get_json()
        # print(data)
        # user = User.query.filter_by(user_type = data['type'], username = data['content']).first()
        # print(user.id, user.username, user.user_type)

        users = User.query.filter_by(user_type = data['type'], username = data['content']).all()
        
        return jsonify(
            code=200,
            message="Success",
            data=[{
                #'id': str(u.id),
                'id': u.sid,
                'name': u.username,
                'type': u.user_type,
                'time': u.created_at
            } for u in users]
        )

    except Exception as e:
        return jsonify(code=500, message=str(e)), 500

@app.route('/delete_user', methods=['POST'])
def delete_user():
    try:
        data = request.get_json()
        # 参数校验
        if 'id' not in data or not data['id']:
            return jsonify(code=400, message="Missing or invalid user id"), 400

        # 查询用户（使用正确的过滤方式）
        user = User.query.filter_by(sid=data['id']).first()
        
        if not user:
            return jsonify(code=404, message="User not found"), 404

        # 直接删除用户对象
        db.session.delete(user)
        db.session.commit()
        
        return jsonify(code=200, message="Deleted successfully"), 200
        
    except SQLAlchemyError as e:  # 更精确的异常捕获
        db.session.rollback()
        app.logger.error(f"Database error: {str(e)}")
        return jsonify(code=500, message="Database operation failed"), 500
    except Exception as e:
        app.logger.error(f"Unexpected error: {str(e)}")
        return jsonify(code=500, message="Internal server error"), 500

@app.route('/add_user', methods=['POST'])
def add_user():
    try:
        data = request.get_json()
        if User.query.filter_by(username=data['name']).first():
            return jsonify({"error": "user already exsits"}), 400
        
        new_user = User(
            username=data['name'],
            user_type=data['type'],
        )
        new_user.created_at = datetime.utcnow()
        new_user.set_password(data['code'])


        db.session.add(new_user)
        db.session.flush()
        new_user.sid = str(new_user.id)
        db.session.commit()
        
        return jsonify(code=200, message="User created"), 200
    except Exception as e:
        return jsonify(code=500, message=str(e)), 500

@app.route('/add_test', methods=['POST'])
def add_test():
    try:
        data = request.get_json()
        required = ['test_name', 'uploader', 'question_ids']
        valid, msg = validate_required(data, required)
        if not valid:
            return jsonify(code=400, message=msg), 400

        questions = [str(item) for item in data['question_ids']]
        uploader = User.query.filter_by(username = data['uploader']).first()

        paper = ExamPaper(
            name = data['test_name'],
            creator_id = uploader.id,
            created_at = datetime.utcnow()
        )
        
        # 预检查所有题目
        for qid in questions:
            question = Question.query.filter_by(sid = qid).first()
            if not question:
                return jsonify({"error": f"题目 {qid} 不存在"}), 404
        
        # 添加题目关联
        for qid in questions:
            # 使用关联代理添加（自动创建PaperQuestion）
            question = Question.query.filter_by(sid = qid).first()
            paper.questions.append( (question, 10) )
        
        db.session.add(paper)
        db.session.flush()
        paper.sid = str(paper.id)
        db.session.commit()

        return jsonify(code=200, message="Test created"), 200
    except Exception as e:
        return jsonify(code=500, message=str(e)), 500


"""

@app.route('/api/register', methods=['POST'])
def register():
    data = request.get_json()
    if User.query.filter_by(username=data['username']).first():
        return jsonify({"error": "用户名已存在"}), 400
    
    new_user = User(
        username=data['username'],
        role=data.get('user_type', 'student')
    )
    new_user.set_password(data['password'])
    db.session.add(new_user)
    db.session.commit()
    return jsonify({"message": "用户创建成功"}), 201

# 修正后的登录路由
@app.route("/api/login", methods=["POST"])
def login():
    auth = request.authorization
    if not auth or not auth.username or not auth.password:
        return jsonify({"error": "需要用户名和密码"}), 401

    user = User.query.filter_by(username=auth.username).first()
    if not user or not user.check_password(auth.password):
        return jsonify({"error": "无效凭证"}), 401

    try:
        token = jwt.encode(
            {
                "user_id": user.id,
                "role": user.role,  # 确保包含角色信息
                "exp": datetime.utcnow() + timedelta(hours=1)
            },
            app.config["SECRET_KEY"],
            algorithm="HS256"
        )
        return jsonify({"token": token})
    except Exception as e:
        return jsonify({"error": "令牌生成失败"}), 500

@app.route('/api/questions', methods=['POST'])
@role_required('teacher')
def create_question():
    user = g.current_user
    try:
        if 'image' in request.files:
            image_file = request.files['image']
            question_data = request.form.to_dict()
            image_data = image_file.read()
        else:
            question_data = request.get_json()
            image_data = None

        new_question = Question(
            type=question_data['type'],
            content=question_data['content'],
            answer=question_data['answer'],
            subject=question_data.get('subject'),
            difficulty=question_data.get('difficulty', 3),
            creator_id=get_current_user().id,
            image_data=image_data
        )
        db.session.add(new_question)
        db.session.commit()
        return jsonify({"question_id": new_question.id}), 201
    except Exception as e:
        db.session.rollback()
        return jsonify({"error": str(e)}), 500

@app.route('/api/papers', methods=['POST'])
@role_required('teacher')
def create_paper():
    user = g.current_user
    data = request.get_json()
    required = ['name', 'questions']
    
    # 字段验证
    if not all(k in data for k in required):
        return jsonify({"error": f"缺少必要字段: {required}"}), 400
        
    try:
        paper = ExamPaper(
            name=data['name'],
            creator_id=user.id
        )
        
        # 预检查所有题目
        for q in data['questions']:
            question = db.session.get(Question, q['id'])
            if not question:
                return jsonify({"error": f"题目 {q['id']} 不存在"}), 404
        
        # 添加题目关联
        for q in data['questions']:
            # 使用关联代理添加（自动创建PaperQuestion）
            paper.questions.append( (db.session.get(Question, q['id']), q['score']) )
        
        db.session.add(paper)
        db.session.commit()
        return jsonify({"paper_id": paper.id}), 201
        
    except Exception as e:
        db.session.rollback()
        app.logger.error(f"组卷失败: {str(e)}", exc_info=True)  # 记录完整堆栈
        return jsonify({"error": "服务器内部错误"}), 500

@app.route('/api/exam/start/<int:paper_id>', methods=['POST'])
@role_required('student')
def start_exam(paper_id):
    try:
        user = g.current_user  # 从上下文获取
        record = ExamRecord(
            user_id=user.id,
            paper_id=paper_id,
            start_time=datetime.utcnow()
        )
        db.session.add(record)
        db.session.commit()
        return jsonify({"record_id": record.id}), 201
    except Exception as e:
        return jsonify({"error": str(e)}), 500

@app.route('/api/exam/submit', methods=['POST'])
@role_required('student')
def submit_answer():
    user = g.current_user
    data = request.get_json()
    exam_answer = ExamAnswer(
        record_id=data['record_id'],
        question_id=data['question_id'],
        user_answer=data['answer']
    )
    db.session.add(exam_answer)
    db.session.commit()
    return jsonify({"status": "答案提交成功"})

@app.route('/api/exam/upload-image', methods=['POST'])
@role_required('student')
def upload_answer_image():
    user = g.current_user
    record_id = request.form.get('record_id')
    image_file = request.files['image']
    
    image = AnswerImage(
        record_id=record_id,
        image_data=image_file.read()
    )
    db.session.add(image)
    db.session.commit()
    return jsonify({"status": "图片上传成功"})


@app.route('/api/grade/<int:record_id>', methods=['POST'])
@role_required('teacher')
def grade_exam(record_id):
    try:
        record = db.session.get(ExamRecord, record_id)
        if not record:
            return jsonify({"error": "考试记录不存在"}), 404
            
        answers = ExamAnswer.query.filter_by(record_id=record_id).all()
        total_score = 0
        
        for answer in answers:
            question = db.session.get(Question, answer.question_id)
            if not question:
                continue

            pq = PaperQuestion.query.filter_by(
                paper_id=record.paper_id,
                question_id=question.id
            ).first()
            if not pq:
                continue

            # 统一处理答案格式
            user_answer = (answer.user_answer or "").strip().lower()
            correct_answer = (question.answer or "").strip().lower()

            if question.type == 'choice':
                if user_answer == correct_answer:
                    total_score += pq.score
                    answer.score = pq.score
            elif question.type == 'fill':
                # 填空题支持多个正确答案（逗号分隔）
                correct_answers = [a.strip() for a in correct_answer.split(',')]
                if user_answer in correct_answers:
                    total_score += pq.score
                    answer.score = pq.score
            # 可扩展其他题型逻辑
            
        record.total_score = total_score
        record.end_time = datetime.utcnow()
        db.session.commit()
        return jsonify({"total_score": total_score})
    except Exception as e:
        db.session.rollback()
        return jsonify({"error": str(e)}), 500

@app.route('/api/papers/<int:paper_id>', methods=['DELETE'])
@role_required('teacher')
def delete_paper(paper_id):
    try:
        paper = db.session.get(ExamPaper, paper_id)
        if not paper:
            return jsonify({"error": "试卷不存在"}), 404
        
        # 删除关联题目关系
        db.session.query(PaperQuestion).filter_by(paper_id=paper_id).delete()
        db.session.delete(paper)
        db.session.commit()
        return jsonify({"message": "试卷删除成功"}), 200
    except Exception as e:
        db.session.rollback()
        return jsonify({"error": str(e)}), 500

# ------------------ 错误处理 ------------------
@app.errorhandler(404)
def not_found(error):
    return jsonify({"error": "资源未找到"}), 404

@app.errorhandler(500)
def internal_error(error):
    return jsonify({"error": "服务器内部错误"}), 500
"""

def create_initial_user():
    with app.app_context():
        # 创建所有数据库表
        db.create_all()
        
        # 检查用户是否已存在
        if not User.query.filter_by(username="rootuser").first():
            # 创建初始用户
            super_user = User(
                username="rootuser",
                #user_type="老师",
                user_type="管理员",
                created_at=datetime.utcnow()
            )
            super_user.set_password("12345")  # 确保有set_password方法

            
            # 提交到数据库
            db.session.add(super_user)
            db.session.flush()
            super_user.sid = str(super_user.id)
            db.session.commit()
            print("Initial user created successfully!")
        else:
            print("Initial user already exists")


# ------------------ 主程序 ------------------
if __name__ == '__main__':
    create_initial_user()
    app.run(host='0.0.0.0', port=5000, debug=True)