function loadContent(e) {
    
    let feedback = $("#reviews-content");
    let review_name = document.getElementById("review-name").value;
    let review_comment = document.getElementById("review-comment").value;

    $.post('get_reviews.php', { name: review_name, comment: review_comment }, function (data) {
        feedback.html(data);
    });
}

function loadPage() {
    let feedback = $("#reviews-content");

    $.post('get_reviews.php', {}, function (data) {
        feedback.html(data);
    });
}

$(window).on('load', loadPage());
document.getElementById("review-send").addEventListener("click", loadContent);