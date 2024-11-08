const aboutSection = document.querySelector('.about-section');
const homeSection = document.querySelector('.home-section');
const logoToPage = document.querySelector('.to-page');

aboutSection.addEventListener('click', function(event) {
    event.preventDefault();
    window.location.href = 'about.html';

});

homeSection.addEventListener('click', function(event) {
    event.preventDefault();
    window.location.href = 'index.html';

});

logoToPage.addEventListener('click', function(event) {
    event.preventDefault();
    window.location.href = 'index.html';

});