const signUpButton = document.getElementById('signUp');
const signInButton = document.getElementById('signIn');
const container = document.getElementById('container');
const login = document.getElementById('login');
const register = document.getElementById('register');

signUpButton.addEventListener('click', () => {
	container.classList.add("right-panel-active");
});

signInButton.addEventListener('click', () => {
	container.classList.remove("right-panel-active");
});

login.addEventListener('click', () => {
	fetch('http://127.0.0.1:8080', {
		method: 'POST', // or 'PUT'
		headers: {
			'Content-Type': 'application/json',
		},
		body: 'SELECT * FROM customer',
	});
});

register.addEventListener('click', () => {
	//do queries for registration
});