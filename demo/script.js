//functions
function processLogin(data) {
	if(data[0]['Success'] === false) {
		console.log("There was an error in the SQL query!");
		console.log(data[0]['Error']);
	}
	else {
		lpassword = document.getElementById("lpassword").value;
		if(data.length > 1 && lpassword === data[1]['password']) {
			var name = data[1]['name'];
			status.innerHTML = "<h2 style=\"color: limegreen;\">Welcome back, " + name + "!</h2>";
			//console.log("Welcome in!!!");
		}
		else {
			status.innerHTML = "<h2 style=\"color: red;\">Incorrect username or password!</h2>";
			//console.log("Incorrect username or password!");
		}

	}
}

function processRegistration(data) {
	if(data[0]['Success'] === false) {
		console.log("The user already exists!");
		status.innerHTML = "<h2 style=\"color: red;\">User already exists!</h2>";
		//console.log(data[0]['Error']);
	}
	else {
		//console.log('Registration was successful!');
		status.innerHTML = "<h2 style=\"color: limegreen;\">Registration was successful!</h2>";
	}
}


const signUpButton = document.getElementById('signUp');
const signInButton = document.getElementById('signIn');
const container = document.getElementById('container');
const login = document.getElementById('login');
const register = document.getElementById('register');
const status = document.getElementById('status');


signUpButton.addEventListener('click', () => {
	container.classList.add("right-panel-active");
});

signInButton.addEventListener('click', () => {
	container.classList.remove("right-panel-active");
});

login.addEventListener('click', () => {
	lemail = document.getElementById("lemail").value;
	var requestString = "SELECT * FROM customer WHERE email=\'" + lemail + "\'";
	fetch('http://127.0.0.1:8080', {
		method: 'POST', // or 'PUT'
		headers: {
			'Content-Type': 'application/json',
		},
		body: requestString,
	}).then((response) => response.json()).then((data) => processLogin(data));
});

register.addEventListener('click', () => {
	//do queries for registration
	let remail = document.getElementById("remail").value;
	let rpassword = document.getElementById("rpassword").value;
	let rname = document.getElementById("rname").value;
	var requestString = "INSERT INTO customer(email, password, name) VALUES (\'" + remail + "\'" + ",\'" + rpassword + "\'" + ",\'" + rname + "\'" + ")";
	fetch('http://127.0.0.1:8080', {
		method: 'POST',
		headers: {
			'Content-Type': 'application/json',
		},
		body: requestString,
	}).then((response) => response.json()).then((data) => processRegistration(data));
});