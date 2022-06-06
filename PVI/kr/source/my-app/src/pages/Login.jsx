import { Form, FormGroup, Button, Modal } from "react-bootstrap";
import "bootstrap/dist/css/bootstrap.min.css";



function LoginForm(props) {
    function validate(){
        var nickname_log = document.getElementById("nickname_log").value;
        var email = document.getElementById("email_log").value;
        var pwd = document.getElementById("password_log").value;
    
        var server = 'http://kr/login.php';
        var formdata = new FormData();
        formdata.append('nickname', nickname_log);
        formdata.append('email', email);
        formdata.append('password', pwd);
        fetch(server, {
            method : 'POST',
            header : {'Content-Type' : 'application/x-www-form-urlencoded'},
            body : formdata
        })
        .then(response => { return response.json(); })
        .then(data => {
            if(!data.validated){
                alert(data.validation_error_text);
                return false;
            }
            if(data.sever_error){
                alert(data.sever_error_text);
                return false;
            }
            props.setUserId(data.id);
            props.setUserName(data.nickname);
            props.onHide();
        });
        
    }

    return (
        <>
            <Modal
            {...props}
            >
                <Modal.Header>
                    <Modal.Title>
                        Log in
                    </Modal.Title>
                </Modal.Header>

                <Modal.Body>
                    <Form>
                        <FormGroup>
                            <Form.Label>Enter your nickname</Form.Label>
                            <Form.Control
                            id="nickname_log"
                            name="nickname_log"
                            type="text"
                            placeholder="Your nickname"
                            />
                        </FormGroup>
                        <FormGroup style={{marginTop: 20}}>
                            <Form.Label>Enter email</Form.Label>
                            <Form.Control
                            id="email_log"
                            name="email_log"
                            type="email"
                            placeholder="example@email.com"
                            
                            />
                        </FormGroup>
                        <FormGroup style={{marginTop: 20}}>
                            <Form.Label>Enter password</Form.Label>
                            <Form.Control
                            id="password_log"
                            name="password_log"
                            type="password"
                            pattern="^(?=.*[0-9])(?=.*[a-z])(?=.*[A-Z])(?=\S+$).{6,}$"
                            
                            />
                        </FormGroup>
                    </Form>
                </Modal.Body>
                
                <Modal.Footer>
                    <Button variant="success" onClick={() => validate()} style={{marginTop: 10}}> 
                        Submit form
                    </Button>
                    <Button variant="danger" onClick={props.onHide} style={{marginTop: 10, marginLeft: 10}}>
                        Close
                    </Button>
                </Modal.Footer>
            </Modal>
        </>
    );
  }
  
  export default LoginForm;