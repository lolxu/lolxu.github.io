// document.addEventListener('DOMContentLoaded', loadProject);

const ProjectNames = 
[
    "simply_rotate",
    "gmtk_2023",
    "sdl_projects",
    "prototype",
    "tencent",
    "average_day",
    "bodycam_shooter",
    "agp",
    "getaway",
    "multiplayer_fps",
    "itp_engine",
    "prime_engine"
]

let ProjectText = [];

for (let i = 0; i < ProjectNames.length; ++i) {
    ProjectText.push("");
    ProjectText[i] = "./data/pages/projects/" + ProjectNames[i];
}

let btnLock = false;
let prevBtnIndex = -1;

function loadProject(button, btnIndex) {
    if (button.getAttribute("class") == "btn btn-color-2 proj-expand-button") {
        window.location.href = ProjectText[btnIndex];
    }
}