$(window).on("beforeunload", function() {
    $.ajax({
        url: "logout.php",
        type: "POST",
        async: false
    });
});