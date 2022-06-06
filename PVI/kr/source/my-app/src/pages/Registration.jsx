import { Form, FormGroup, Button, Modal } from "react-bootstrap";
import "bootstrap/dist/css/bootstrap.min.css";

function RegisterForm(props) {
    function validate(){
        var fpsw = document.getElementById("password").value;
        var fpsw_repeat = document.getElementById("confirmpass").value;
        var nickname = document.getElementById("nickname").value;
        var email = document.getElementById("email").value;
        if(fpsw !== fpsw_repeat)
        {
            alert("Passwords are not the same");
            return false;
        }
        var server = 'http://kr/registration.php';
        var formdata = new FormData();
        formdata.append('nickname', nickname);
        formdata.append('email', email);
        formdata.append('password', fpsw);
        fetch(server, {
            method : 'POST',
            header : {'Content-Type' : 'application/json'},
            body : formdata
        })
        .then(response => {return response.json(); } )
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
                    Sign in
                </Modal.Header>

                <Modal.Body>
                    <Form>
                        <FormGroup>
                            <Form.Label>Enter your nickname</Form.Label>
                            <Form.Control
                                id="nickname"
                                name="nickname"
                                type="text"
                                placeholder="Your nickname"
                            />
                        </FormGroup>
                        <FormGroup style={{marginTop: 20}}>
                            <Form.Label>Enter email</Form.Label>
                            <Form.Control
                                id="email"
                                name="email"
                                type="email"
                                placeholder="example@email.com"
                                
                            />
                        </FormGroup>
                        <FormGroup style={{marginTop: 20}}>
                            <Form.Label>Enter password</Form.Label>
                            <Form.Control
                                id="password"
                                name="password"
                                type="password"
                                pattern="^(?=.*[0-9])(?=.*[a-z])(?=.*[A-Z])(?=\S+$).{6,}$"
                                
                            />
                        </FormGroup>
                        <FormGroup style={{marginTop: 20}}>
                            <Form.Label>Comfirm password</Form.Label>
                            <Form.Control
                                id="confirmpass"
                                name="confirmpass"
                                type="password"
                                pattern="^(?=.*[0-9])(?=.*[a-z])(?=.*[A-Z])(?=\S+$).{6,}$"
                                
                            />
                        </FormGroup>
                    </Form>
                </Modal.Body>

                <Modal.Footer>
                    <Button type="submit" variant="success" onClick={() => validate()} style={{marginTop: 10}}>
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

  export default RegisterForm;