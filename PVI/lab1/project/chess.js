function closeForm() {
    document.getElementById("Form").style.display = "none";
    document.getElementById("pageName").style.display = "";
}

function openForm() {
    document.getElementById("Form").style.display = "block";
    document.getElementById("pageName").style.display = "none";
}

function GetTr(img){
    return img.parentElement.parentElement.parentElement;    
}

function GetTd(img){
    return img.parentElement.parentElement;    
}

function GetDiv(img){
    return img.parentElement;    
}

var isWhiteTurn = true;
const circleElements = [];
const enemyElements = [];
var checkedElement;

function TagCell(e) {
    var img = document.createElement("img");
    img.src = "Resources/redCircle.png";
    img.className = "circle";
    img.setAttribute("onclick","MoveFigure(event);");
    var figure = e.srcElement || e.target;
    while(circleElements.length){
        GetDiv(circleElements[circleElements.length - 1]).removeChild(circleElements[circleElements.length - 1]);
        circleElements.pop();
    }
    if(enemyElements.includes(figure)){
        var cell = GetDiv(figure);
        cell.removeChild(figure);
        cell.appendChild(checkedElement);
        isWhiteTurn = !isWhiteTurn;
        while(enemyElements.length){
            enemyElements[enemyElements.length-1].style.border = "";
            enemyElements[enemyElements.length-1].style.borderRadius = ""; 
            enemyElements.pop();
        }
        return;
    }
    if((isWhiteTurn && figure.className.includes("black")) || (!isWhiteTurn && figure.className.includes("white"))){
        return;
    }
    while(enemyElements.length){
        enemyElements[enemyElements.length-1].style.border = "";
        enemyElements[enemyElements.length-1].style.borderRadius = ""; 
        enemyElements.pop();
    }
    checkedElement = figure;
    // White and black kings.
    if (figure.className.includes("white king") || figure.className.includes("black king")){
        // without border.
        if((GetTr(figure).rowIndex != 7 && GetTr(figure).rowIndex != 0) 
            && (GetTd(figure).cellIndex != 0 && GetTd(figure).cellIndex!= 7)){
            var childrens = GetTr(figure).previousElementSibling.children;
            var leftUpperElement;
            for (var i = 0; i < childrens.length; ++i) {
                if(childrens[i].cellIndex == (GetTd(figure).cellIndex - 1)){
                    leftUpperElement = childrens[i];
                    break;
                }
            }
            TagSquare(leftUpperElement, 3, 3, figure.className);    
        }
        // Right column
        else if(GetTd(figure).cellIndex == 7){
            // Right lower
            if(GetTr(figure).rowIndex == 7){
                var childrens = GetTr(figure).previousElementSibling.children;
                var leftUpperElement;
                for (var i = 0; i < childrens.length; ++i) {
                    if(childrens[i].cellIndex == (GetTd(figure).cellIndex - 1)){
                       leftUpperElement = childrens[i];
                       break;
                    }
                }
                TagSquare(leftUpperElement, 2, 2, figure.className);
            }
            // Right upper
            else if(GetTr(figure).rowIndex == 0){
                var leftUpperElement = GetTd(figure).previousElementSibling;
                TagSquare(leftUpperElement, 2, 2, figure.className);
            }
            // Others
            else{
                var childrens = GetTr(figure).previousElementSibling.children;
                var leftUpperElement;
                for (var i = 0; i < childrens.length; ++i) {
                    if(childrens[i].cellIndex == (GetTd(figure).cellIndex - 1)){
                        leftUpperElement = childrens[i];
                        break;
                    }
                }
                TagSquare(leftUpperElement, 2, 3, figure.className);
            }
        }
        // Left column
        else if(GetTd(figure).cellIndex == 0){
            // Left lower
            if(GetTr(figure).rowIndex == 7){
                var childrens = GetTr(figure).previousElementSibling.children;
                var leftUpperElement;
                for (var i = 0; i < childrens.length; ++i) {
                    if(childrens[i].cellIndex == GetTd(figure).cellIndex){
                       leftUpperElement = childrens[i];
                       break;
                    }
                }
                TagSquare(leftUpperElement, 2, 2, figure.className); 
            }
            // Left upper
            else if(GetTr(figure).rowIndex == 0){
                var leftUpperElement = GetTd(figure);
                TagSquare(leftUpperElement, 2, 2, figure.className);
            }
            // Others
            else{
                var childrens = GetTr(figure).previousElementSibling.children;
                var leftUpperElement;
                for (var i = 0; i < childrens.length; ++i) {
                    if(childrens[i].cellIndex == GetTd(figure).cellIndex){
                        leftUpperElement = childrens[i];
                        break;
                    }
                }
                TagSquare(leftUpperElement, 2, 3, figure.className);
            }
        }
        // Upper and lower row without left and right cols
        else {
            // Lower
            if(GetTr(figure).rowIndex == 7){
                var childrens = GetTr(figure).previousElementSibling.children;
                var leftUpperElement;
                for (var i = 0; i < childrens.length; ++i) {
                    if(childrens[i].cellIndex == (GetTd(figure).cellIndex - 1)){
                       leftUpperElement = childrens[i];
                       break;
                    }
                }
                TagSquare(leftUpperElement, 3, 2, figure.className); 
            }
            // Upper
            else{
                var leftUpperElement = GetTd(figure).previousElementSibling;
                TagSquare(leftUpperElement, 3, 2, figure.className);
            }   
        }
    }
    // White and black pawn.
    else if (figure.className.includes("white pawn") || figure.className.includes("black pawn")){
        if((GetTr(figure).rowIndex != 0 && figure.className.includes("white")) || (GetTr(figure).rowIndex != 7 && figure.className.includes("black"))){
            var childrens;
            if(figure.className.includes("white")){
                childrens = GetTr(figure).previousElementSibling.children;
            }else if(figure.className.includes("black")){
                childrens = GetTr(figure).nextElementSibling.children;
            }
            for (var i = 0; i < childrens.length; ++i) {
                if((childrens[i].cellIndex == (GetTd(figure).cellIndex - 1) && (childrens[i].children)[0].hasChildNodes())
                    || (childrens[i].cellIndex == (GetTd(figure).cellIndex + 1) && (childrens[i].children)[0].hasChildNodes())){
                    var divChilds = (childrens[i].children)[0].children;            
                    for(var j = 0; j < divChilds.length; ++j){
                        if(divChilds[j].className.includes("figure") 
                        && ((divChilds[j].className.includes("black")  && figure.className.includes("white"))
                        || (divChilds[j].className.includes("white") && figure.className.includes("black")))){
                            enemyElements.push(divChilds[j]);
                            break;
                        }
                    }
                }
                else if(childrens[i].cellIndex == GetTd(figure).cellIndex){
                    if(!(childrens[i].children)[0].hasChildNodes()){
                        (childrens[i].children)[0].appendChild(img);
                        circleElements.push(img);
                    }else{
                        var divChilds = (childrens[i].children)[0].children;
                        var hasFigure = false;
                        for(var j = 0; j < divChilds.length; ++j){
                            if(divChilds[j].className.includes("figure")){
                                hasFigure = true;
                            }
                        }
                        if(!hasFigure){
                            (childrens[i].children)[0].appendChild(img);
                            circleElements.push(img);
                        }
                    }
                }
                else if(childrens[i].cellIndex == (GetTd(figure).cellIndex + 2)){
                    break;
                }
            }
        }
    }
    for(var enIdx = 0; enIdx < enemyElements.length; ++enIdx){
        enemyElements[enIdx].style.border = "2px dashed red";
        enemyElements[enIdx].style.borderRadius = "3px"; 
    }
}

function TagSquare(leftUpperElement, colCount, rowCount, figureClassName){
    var i = 0;
    var j = 0;
    var currentElement = leftUpperElement;
    while (true){
        while(true){
            var img = document.createElement("img");
            img.src = "Resources/redCircle.png";
            img.className = "circle";
            img.setAttribute("onclick","MoveFigure(event);");
            if(!(currentElement.children)[0].hasChildNodes()){
                (currentElement.children)[0].appendChild(img);
                circleElements.push(img);
            }else{
                var divChilds = (currentElement.children)[0].children;
                var hasFigure = false;
                for(var m = 0; m < divChilds.length; ++m){
                    if(divChilds[m].className.includes("figure")){
                        hasFigure = true;
                        if((divChilds[m].className.includes("white") && figureClassName.includes("black"))
                        || (divChilds[m].className.includes("black") && figureClassName.includes("white"))){
                            enemyElements.push(divChilds[m]);
                        }
                    }
                }
                if(!hasFigure){
                    (currentElement.children)[0].appendChild(img);
                    circleElements.push(img);
                }
            }
            ++j;
            if (j == colCount){
                j = 0;
                break;
            }
            currentElement = currentElement.nextElementSibling;
        }
        ++i;
        if (i >= rowCount){
            break;
        }
        var childrens = currentElement.parentElement.nextElementSibling.children;
        for (var n = 0; n < childrens.length; ++n) {
            if(childrens[n].cellIndex == leftUpperElement.cellIndex ){
                currentElement = childrens[n];
            }
        }
    }
}

function MoveFigure(e){
    var figure = e.srcElement || e.target;
    var cell = GetDiv(figure);
    while(circleElements.length){
        GetDiv(circleElements[circleElements.length - 1]).removeChild(circleElements[circleElements.length - 1]);
        circleElements.pop();
    }
    while(enemyElements.length){
        enemyElements[enemyElements.length-1].style.border = "";
        enemyElements[enemyElements.length-1].style.borderRadius = ""; 
        enemyElements.pop();
    }
    cell.appendChild(checkedElement);
    isWhiteTurn = !isWhiteTurn;
}