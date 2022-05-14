import { Form, FormGroup, Button, Col, Row } from "react-bootstrap";
import "bootstrap/dist/css/bootstrap.min.css";

const mystyle = {
  width: "25%",
  left: "55%",
  top: "10%",
  position: "absolute"
};

var b;
var f;
var c;

function openform(formName) {
  f = document.getElementById(formName);
  b = document.getElementById("buttons");
  c = document.getElementById("RandomImage");
  f.style.display = "block";
  b.style.display = "none";
  c.style.display = "none";
}

function closeform() {
    b.style.display = "block";
    c.style.display = "block";
    f.style.display = "none";
}

function validate(e){
  e.preventDefault();
  if(f.id==="LogInForm")
  {
    var nickname_log = document.getElementById("nickname_log").value;
    if(nickname_log === "")
    {
       console.log("Empty" + nickname_log)
        alert("Enter your nickname");
        return false;
    }
  }
  else if(f.id==="SighInForm")
  {
    var fpsw = document.getElementById("password").value;
    var fpsw_repeat = document.getElementById("confirmpass").value;
    var nickname = document.getElementById("nickname").value;
    if(fpsw !== fpsw_repeat)
    {
        alert("Passwords are not the same");
        return false;
    }
    if(nickname === "")
    {
        alert("Enter your nickname");
        return false;
    }
  }
  f.submit();
}

function MyForm() {
  return (
    <div className="formsdivs" style={mystyle}>
      <div id="buttons">
        <Row>
          <Col>
            <Button className="openLogInForm" style={{marginRight: 10}} onClick={()=>openform("LogInForm")}>
              Log in
            </Button>
            <Button className="openSignInForm" onClick={()=>openform("SighInForm")}>
              Sign in
            </Button>
          </Col>
        </Row>
      </div>
      <div className="divForm">
        <Form
          id="SighInForm"
          className="text-center"
          style={{ display: "none", border: "1px solid gray", borderRadius: "10px", padding: 10 }}
        >
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
              required
            />
          </FormGroup>
          <FormGroup style={{marginTop: 20}}>
            <Form.Label>Enter password</Form.Label>
            <Form.Control
              id="password"
              name="password"
              type="password"
              pattern="^(?=.*[0-9])(?=.*[a-z])(?=.*[A-Z])(?=\S+$).{6,}$"
              required
            />
          </FormGroup>
          <FormGroup style={{marginTop: 20}}>
            <Form.Label>Comfirm password</Form.Label>
            <Form.Control
              id="confirmpass"
              name="confirmpass"
              type="password"
              pattern="^(?=.*[0-9])(?=.*[a-z])(?=.*[A-Z])(?=\S+$).{6,}$"
              required
            />
          </FormGroup>
          <Button type="submit" variant="success" onClick={el => validate(el)} style={{marginTop: 10}}>
            Submit form
          </Button>
          <Button variant="danger" onClick={closeform} style={{marginTop: 10, marginLeft: 10}}>
            Close
          </Button>
        </Form>
      </div>

      <div className="divForm">
        <Form
          id="LogInForm"
          className="text-center"
          style={{ display: "none", border: "1px solid gray", borderRadius: "10px", padding: 10 }}
        >
          <FormGroup>
            <Form.Label>Enter your nickname</Form.Label>
            <Form.Control
              id="nickname_log"
              name="nickname"
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
              required
            />
          </FormGroup>
          <FormGroup style={{marginTop: 20}}>
            <Form.Label>Enter password</Form.Label>
            <Form.Control
              id="password_log"
              name="password_log"
              type="password"
              pattern="^(?=.*[0-9])(?=.*[a-z])(?=.*[A-Z])(?=\S+$).{6,}$"
              required
            />
          </FormGroup>
          <Button type="submit" variant="success" onClick={el => validate(el)} style={{marginTop: 10}}> 
            Submit form
          </Button>
          <Button variant="danger" onClick={closeform} style={{marginTop: 10, marginLeft: 10}}>
            Close
          </Button>
        </Form>
      </div>
    </div>
  );
}

export default MyForm;
