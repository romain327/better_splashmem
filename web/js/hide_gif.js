function hide_pwrup() {
    var pwrup_gif = document.getElementById("pwrup_gif");
    if (pwrup_gif.style.visibility === "visible") {
        pwrup_gif.style.visibility = "hidden";
    }
    else {
        pwrup_gif.style.visibility = "visible";
    }
}