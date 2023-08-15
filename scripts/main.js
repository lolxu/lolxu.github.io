function toggleMenu() {
    const menu = document.querySelector(".menu-links");
    const icon = document.querySelector(".small-icon");
    menu.classList.toggle("open");
    icon.classList.toggle("open");
}

let isContentShowing = false;
let latestFileName;

function loadHtml() {

    const loadExperience = document.getElementById("about-experience_button");
    const loadEducation = document.getElementById("about-education_button");
    const contentContainer = document.getElementById("details-container");
    let experienceVisible = false;
    let educationVisible = false;

    if (loadExperience != null) {
        loadExperience.addEventListener('click', async function() {
            try {
                educationVisible = false;
                if (experienceVisible) {
                    contentContainer.style.opacity = 0;
                    
                    setTimeout(() => {
                        contentContainer.innerHTML = '<p> &gt; Click above buttons to reveal... </p>';
                        experienceVisible = false;
                        contentContainer.style.opacity = 1;
                    }, 300);
                }
                else {
                    const response = await fetch('./data/pages/experience.html');
                    const html = await response.text();
                    contentContainer.style.opacity = 0;
                    setTimeout(() => {
                        contentContainer.innerHTML = html;
                        experienceVisible = true;
                        contentContainer.style.opacity = 1;
                    }, 300);
                }
                // console.log(experienceVisible, educationVisible);
            } catch (error) {
            console.error('Error loading external page:', error);
            }
        });
    }

      if (loadEducation != null) {
        loadEducation.addEventListener('click', async function() {
            try {
                experienceVisible = false;
                if (educationVisible) {
                    contentContainer.style.opacity = 0;
                    
                    setTimeout(() => {
                        contentContainer.innerHTML = '<p> &gt; Click above buttons to reveal... </p>';
                        educationVisible = false;
                        contentContainer.style.opacity = 1;
                    }, 300);
                }
                else {
                    const response = await fetch('./data/pages/education.html');
                    const html = await response.text();
                    contentContainer.style.opacity = 0;
                    setTimeout(() => {
                        contentContainer.innerHTML = html;
                        educationVisible = true;
                        contentContainer.style.opacity = 1;
                    }, 300);
                }
                // console.log(experienceVisible, educationVisible);
            } catch (error) {
              console.error('Error loading external page:', error);
            }
          });
      }
      
}

function clickEffect(e){
    var d=document.createElement("div");
    d.className="clickEffect";
    d.style.top=e.clientY+"px";d.style.left=e.clientX+"px";
    document.body.appendChild(d);
    d.addEventListener('animationend',function(){d.parentElement.removeChild(d);}.bind(this));
}

document.addEventListener('click',clickEffect);
document.addEventListener('DOMContentLoaded', loadHtml);