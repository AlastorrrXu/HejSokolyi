function switchLanguage(lang) {
    if (lang === 'en') {
        document.getElementById('content-en').classList.remove('hidden');
        document.getElementById('content-uk').classList.add('hidden');
    } else if (lang === 'uk') {
        document.getElementById('content-en').classList.add('hidden');
        document.getElementById('content-uk').classList.remove('hidden');
    }
}
