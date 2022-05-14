import React from "react";
import { Button } from "react-bootstrap";
import "bootstrap/dist/css/bootstrap.min.css";
var imageurl;

function getImage() {
  fetch("https://random.dog/woof.json?ref=apilist.fun")
    .then((response) => {
      return response.json();
    })
    .then((data) => {
        imageurl = data["url"];
    });
  document.getElementById("randomImg").src = imageurl;
}

const mystyle = {
    width: "25%",
    left: "55%",
    top: "15%",
    position: "absolute"
  };

function RandomImage() {
  return (
    <div id="RandomImage" className="RandomImage" style={mystyle}>
      <Button variant="primary" onClick={getImage} className="mx-auto">
        Random image
      </Button>
    </div>
  );
}

export default RandomImage;
