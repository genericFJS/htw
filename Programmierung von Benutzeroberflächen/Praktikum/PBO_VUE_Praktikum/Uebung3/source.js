new Vue({
    el: '#app',
    data: {
        password: '',
        categories: [
            {name: 'JavaScript', sub: ['Vue.js', 'React', 'Angular2']},
            {name: 'Databases', sub: ['MySQL', 'PostgreSQL', 'MariaDB']},
            {name: 'Operating Systems', sub:['macOS','Linux', 'Windows']}
        ]
    }
});