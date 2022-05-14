import React  from "react";

let s=null;
let b=false;

function get(str)
{
    if(!str.src.includes("empty.png")||b===true)
    {
        if(s===null)
        {
            s = str;
            b=true;
        }
        else if(str!==s)
        {
            str.src = s.src;
            s.src = "images/empty.png";
            b=false;
            s=null;
        }
    }
}

const mystyle = {
    width: "60%",
    float: "left"
};

function ChessField() {
  return (
    <div className="ChessField" style={mystyle}>
      <table>
        <tr>
            <td>
                <div className="block">
                    <div className="number">8</div>
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
        </tr>
        <tr>
            <td>
                <div className="block">
                    <div className="number">7</div>
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/bb.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
        </tr>
        <tr>
            <td>
                <div className="block">
                    <div className="number">6</div>
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/wp.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
        </tr>
        <tr>
            <td>
                <div className="block">
                    <div className="number">5</div>
                    <img alt="" src="images/wb.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
        </tr>
        <tr>
            <td>
                <div className="block">
                    <div className="number">4</div>
                    <img alt="" src="images/wp.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/bk.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
        </tr>
        <tr>
            <td>
                <div className="block">
                    <div className="number">3</div>
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
        </tr>
        <tr>
            <td>
                <div className="block">
                    <div className="number">2</div>
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
        </tr>
        <tr>
            <td>
                <div className="block">
                    <div className="number">1</div>
                    <div className="letter">a</div>
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <div className="letter">b</div>
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <div className="letter">c</div>
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <div className="letter">d</div>
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <div className="letter">e</div>
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <div className="letter">f</div>
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <div className="letter">g</div>
                    <img alt="" src="images/empty.png" onClick={el => get(el.target)}/>
                </div>
            </td>
            <td>
                <div className="block">
                    <div className="letter">h</div>
                    <img alt="" src="images/wk.png" onClick={el => get(el.target)}/>
                </div>
            </td>
        </tr>
      </table>
    </div>
  );
}

export default ChessField;