import React  from "react";

const mystyle = {
    width: "40%",
    float: "right"
};
var b;
var f;


function goToForm(form)
{
    f = document.getElementById(form);
    b = document.getElementById("buttons");
    f.style.display = "block";
    b.style.display = "none";
}

function back()
{
    b.style.display = "block";
    f.style.display = "none";
}

function validate()
{
    var x;
    if(f.id==="LogInForm")
    {
        x = document.forms[f.name];
        if(x["email"].value === ""||x===null)
        {
            alert("Fill Email");
            return false;
        }
        if(x["pass"].value === ""||x===null)
        {
            alert("Fill Password");
            return false;
        }

        alert(x["email"].value + " " + x["pass"].value)
        return false;
    }
    else if(f.id==="SignInForm")
    {
        x = document.forms[f.name];
        if(x["email"].value === ""||x===null)
        {
            alert("Fill Email");
            return false;
        }
        if(x["pass"].value === ""||x===null)
        {
            alert("Fill Password");
            return false;
        }
        if(x["rpass"].value === ""||x===null)
        {
            alert("Fill Repeat Password");
            return false;
        }
        if(x["pass"].value !== x["rpass"].value)
        {
            alert("Repeat Password is not correct");
            return false;
        }
        if(x["gender"].value === ""||x===null)
        {
            alert("Please select your gender");
            return false;
        }
        if(x["check"].checked === false)
        {
            alert("Please agree with the term of services");
            return false;
        }
        alert(x["email"].value + " " + x["pass"].value + " " + x["gender"].value)
        return false;
    }
}


function MyForm() {
    return (
    <div className="MyForm" style={mystyle}>
        <br/>
        <button className="button-3" onClick={()=>window.open("https://en.wikipedia.org/wiki/Rules_of_chess", "_blank")}>Rules</button>
        <button className="button-3" onClick={()=>window.open("https://www.chess.com/puzzles/problem/48779", "_blank")}>Puzzle</button>
        <br/>
        <div>
            <div id="buttons">
                <button className="button-3" onClick={()=>goToForm("SignInForm")}>Register</button>
                <button className="button-3" onClick={()=>goToForm("LogInForm")}>LogIn</button>
            </div>
            <div className="justForm">
                <form id="LogInForm" style={{display: "none"}} name="LogInForm" method="post">
                <label>Email:</label>
                    <br/>
                    <input class="frm" type="text" pattern="^[a-z0-9._%+-]+@[a-z0-9.-]+\.[a-z]{2,4}$" name="email"/>
                    <br/>
                    <label>Password:</label>
                    <br/>
                    <input class="frm" type="password" pattern="^(?=.*[0-9])(?=.*[a-z])(?=.*[A-Z])(?=\S+$).{6,}$" name="pass"/>
                    <br/>
                    <input class="button-3" type="submit" value="Send" onClick={validate}/>
                    <input class="button-3" type="reset" value="Cancel" onClick={back}/>
                </form>
            </div>
            <div className="justForm">
                    <form id="SignInForm" style={{display: "none"}} name="SignInForm">
                        <label>Email:</label>
                        <br/>
                        <input class="frm" type="text" pattern="^[a-z0-9._%+-]+@[a-z0-9.-]+\.[a-z]{2,4}$" name="email"/>
                        <br/>
                        <label>Password:</label>
                        <br/>
                        <input class="frm" type="password" pattern="^(?=.*[0-9])(?=.*[a-z])(?=.*[A-Z])(?=\S+$).{6,}$" name = "pass"/>
                        <br/>
                        <label>Repeat password:</label>
                        <br/>
                        <input class="frm" type="password" pattern="^(?=.*[0-9])(?=.*[a-z])(?=.*[A-Z])(?=\S+$).{6,}$" name = "rpass"/>
                        <br/>
                        <label>Select your gender or write</label>
                        <br/>
                        <br/>
                        <select name="gender">
                            <option value="Male">Male</option>
                            <option value="Female">Female</option>
                            <option value="Other">Other</option>
                        </select>
                        <br/>
                        <br/>
                        <input type="checkbox" name="check"/>
                        <label>I agree with the term of services</label>
                        <br/>
                        <input class="button-3" type="submit" value="Send" onClick={validate}/>
                        <input class="button-3" type="reset" value="Cancel" onClick={back}/>
                    </form>
                </div>
        </div>
    </div>

    );
  }
  
  export default MyForm;