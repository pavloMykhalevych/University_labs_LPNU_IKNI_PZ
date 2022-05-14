import "bootstrap/dist/css/bootstrap.min.css";
import { Nav, Button } from "react-bootstrap";

function Links() {
  return (
    <Nav style={{margin: 20}}>
      <Nav.Item >
      <Button variant="primary">
      <Nav.Link 
          style={{color:"white"}}
          href="https://www.chess.com/puzzles/problem/491418"
          target="_blank"
        >
          Puzzle
        </Nav.Link></Button> 
      </Nav.Item>
      <Nav.Item style={{marginLeft : 5}}>
      <Button variant="primary">
        <Nav.Link 
        style={{color:"white"}}
          href="https://en.wikipedia.org/wiki/Rules_of_chess"
          target="_blank"
        >
          Chess rules
        </Nav.Link></Button> 
      </Nav.Item>
    </Nav>
  );
}

export default Links;
