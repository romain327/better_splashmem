function display() {
    var popup = document.getElementById("connection_popup");
    popup.style.visibility = "visible";
}

function hide() {
    var popup = document.getElementById("connection_popup");
    popup.style.visibility = "hidden";
}

function display2() {
    var popup = document.getElementById("select_name_popup");
    popup.style.visibility = "visible";
}

function hide2() {
    var popup = document.getElementById("select_name_popup");
    popup.style.visibility = "hidden";
}

function display3() {
    var popup = document.getElementById("upload_file_popup");
    popup.style.visibility = "visible";
}

function hide3() {
    var popup = document.getElementById("upload_file_popup");
    popup.style.visibility = "hidden";
}

function parentWidth(elem) {
    return elem.parentElement.clientWidth;
}
