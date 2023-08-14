// document.addEventListener('DOMContentLoaded', loadProject);

const ProjectNames = 
[
    "simply_rotate"
]

let ProjectText = [];

for (let i = 0; i < ProjectNames.length; ++i) {
    ProjectText.push("");
    ProjectText[i] = "./data/pages/projects/" + ProjectNames[i] + ".html";

    // fetch("./data/pages/projects/" + ProjectNames[i] + ".html")
    // .then( r => r.text())
    // .then( t => {ProjectText[i] = t; console.log(ProjectText[i]); console.log(i);})
    
}

let btnLock = false;
let prevBtnIndex = -1;

function loadProject(button, btnIndex) {
    if (button.getAttribute("class") == "btn btn-color-2 proj-expand-button") {
        window.location.href = ProjectText[btnIndex];
    }
    // let projTextArea = document.getElementById("project_detailed_description");
    // var x = document.getElementsByClassName("proj-expand-button-active");
    // if (button.getAttribute("class") == "btn btn-color-2 proj-expand-button-active") {
    //     x[0].className = "btn btn-color-2 proj-expand-button";
    //     projTextArea.innerHTML = "";
    //     projTextArea.style.opacity = 0;
    //     // document.getElementById(button.getAttribute("id")).innerHTML = "Expand";
    // }
    // else {
    //     if (x.length != 0) {
    //         x[0].className = "btn btn-color-2 proj-expand-button";
    //         projTextArea.innerHTML = "";
    //         projTextArea.style.opacity = 0;
    //         // document.getElementById(button.getAttribute("id")).innerHTML = "Expand";
    //     }

    //     projTextArea.innerHTML = ProjectText[btnIndex];
    //     projTextArea.style.opacity = 1;
    //     document.getElementById(button.getAttribute("id")).className = "btn btn-color-2 proj-expand-button-active";
    //     // document.getElementById(button.getAttribute("id")).innerHTML = "Shrink";
    // }
}