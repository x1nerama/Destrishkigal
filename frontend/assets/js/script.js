var homeBtn = document.getElementById("homeBtn");
var logBtn = document.getElementById("logBtn");
var homeContent = document.getElementById("homePage");
var logContent = document.getElementById("logPage");
var line1 = document.getElementById("line1")
var line2 = document.getElementById("line2")
    
line1.style.width = "10%";

homeBtn.addEventListener("click", function() {
    homeContent.style.display = "block";
    logContent.style.display = "none";
    line1.style.width = "10%";
    line2.style.width = "0"

    /* Customizing the homeBtn */
    homeBtn.style.color = "hsl(0, 0%, 70%)"; 
    homeBtn.style.backgroundColor = "hsl(240, 1%, 28%)";
    homeBtn.style.fontWweight = "bold";
    homeBtn.style.borderRadius = "5px";
    
    logBtn.style.color = "hsl(0, 0%, 0%)";
    logBtn.style.fontWweight = "normal";
    logBtn.style.border = "none";
});
    
logBtn.addEventListener("click", function() {
    homeContent.style.display = "none";
    logContent.style.display = "block";
    line1.style.width = "0";
    line2.style.width = "10%";
    
    /* Customizing the logBtn */
    logBtn.style.color = "hsl(0, 0%, 70%)";
    logBtn.style.backgroundColor = "hsl(240, 1%, 28%)";
    logBtn.style.fontWweight = "bold";
    logBtn.style.borderRadius = "5px";

    /* Reset homeBtn */
    homeBtn.style.color = "hsl(0, 0%, 0%)";
    homeBtn.style.fontWweight = "normal";
    homeBtn.style.border = "none";
});