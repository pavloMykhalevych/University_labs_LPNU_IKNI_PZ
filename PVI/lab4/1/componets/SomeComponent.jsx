import React  from "react";
import { Button } from "react-bootstrap";
import { Image } from "react-bootstrap";
import 'bootstrap/dist/css/bootstrap.min.css';

var pickurl;

function lpick()
{
    fetch('https://random.dog/woof.json?ref=apilist.fun').then((response) => { return response.json();}).then((data) => {pickurl = data['url'];});
    document.getElementById("img").src = pickurl;
}

const mystyle = {
    width: "40%",
    float: "left"
};

function SomeComponent() {
    return (
        <div className="SomeComponent" style={mystyle}>
            <Button variant="primary" onClick={lpick} className="mx-2">Сlick me</Button>
            <Image id="img" src = "https://random.dog/b1168d67-1cd7-4998-b0e3-9db93e07ee5d.jpg" roundedCircle/>
        </div>
    );
  }
  
  export default SomeComponent;