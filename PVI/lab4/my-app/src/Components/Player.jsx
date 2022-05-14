import { Image, Row, Col } from "react-bootstrap";
import "bootstrap/dist/css/bootstrap.min.css";

const myimagestyle = {
  position: "absolute",
  top: "1%",
  right: "2%",
};

function Player() {
  return (
    <div style={myimagestyle}>
      <Row>
        <Col>
          <span id="playerNickname"></span>
        </Col>
        <Col>
          <Image
            style={{
              maxWidth: 70,
              maxHeight: 70,
            }}
            id="randomImg"
            src="https://random.dog/2f6fc1b0-25a4-4890-a434-edbb4a23daf0.jpeg"
            roundedCircle
          />
        </Col>
      </Row>
    </div>
  );
}

export default Player;
