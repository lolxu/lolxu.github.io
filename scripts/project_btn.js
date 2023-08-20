// document.addEventListener('DOMContentLoaded', loadProject);

const ProjectNames = 
[
    "simply_rotate",
    "gmtk_2023",
    "sdl_projects",
    "prototype",
    "tencent",
    "average_day"
]

let ProjectText = [];

for (let i = 0; i < ProjectNames.length; ++i) {
    ProjectText.push("");
    ProjectText[i] = "./data/pages/projects/" + ProjectNames[i];

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
}