// Rafraichissement du classement
document.addEventListener('DOMContentLoaded', function() {
    refreshRanking();
});

setInterval(refreshRanking, 1000);

function refreshRanking() {
    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function() {
        if (xhr.readyState == 4 && xhr.status == 200) {
            document.querySelector('#ranking').innerHTML = xhr.responseText;
        }
    };
    xhr.open('GET', 'display_ranking.php', true);
    xhr.send();
}