// Rafraichissement du classement
document.addEventListener('DOMContentLoaded', function() {
    refreshRanking();
});

setInterval(refreshRanking, 1000);

function refreshRanking() {
    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function() {
        if (xhr.readyState == 4 && xhr.status == 200) {
            document.querySelector('#display_ranking').innerHTML = xhr.responseText;
        }
    };
    xhr.open('GET', 'refresh_ranking.php', true);
    xhr.send();
}

// Gestion du choix des librairies
document.addEventListener('DOMContentLoaded', function() {
    refreshLibs();
});

setInterval(refreshLibs, 20000)

function refreshLibs() {
    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function() {
        if (xhr.readyState == 4 && xhr.status == 200) {
            document.querySelector('#libs_checkboxes').innerHTML = xhr.responseText;
        }
    };
    xhr.open('GET', 'refresh_libs.php', true);
    xhr.send();
}

// Gestion de la largeur du canvas
function getDisplayGameWidth() {
    var displayGame = document.getElementById('display_game');
    var width = displayGame.offsetWidth;
    return width;
}

function updateCanvasWidth() {
    var displayGameWidth = getDisplayGameWidth();
    var canvas = document.getElementById('game_canvas');
    canvas.width = displayGameWidth;
}

document.addEventListener('DOMContentLoaded', function() {
    updateCanvasWidth();
});

window.addEventListener('resize', function() {
    updateCanvasWidth();
});