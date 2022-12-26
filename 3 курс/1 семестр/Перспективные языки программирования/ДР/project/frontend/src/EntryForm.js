import React, { useState } from "react";
import { useFormik } from "formik";
import { useNavigate } from 'react-router-dom';

const EntryForm = (props) => {
	const [error, setError] = useState("");
	const navigate = useNavigate();
	
	const formik = useFormik({
		initialValues: { login: "", password: "" },
		onSubmit: async values => {			
			let formData = new FormData();
			formData.append('login', values['login']);
			formData.append('password', values['password']);
			
			let response = await fetch(props.mode == "login" ? 'http://localhost:5000/users/login' : 'http://localhost:5000/users/signup', {
				method: 'POST',
				body: formData
			});
			
			let result = await response.json();
			
			if (result != null) {
				window.localStorage.setItem('nickname', JSON.stringify(result.name));
				navigate('/main');
			}
			else{
				setError(props.mode == "login" ? "User wasn't found" : "User already exist");
			}
		}
	});
	return (
		<div className="container">
			<div className="row justify-content-lg-center">
				{ error }
			</div>
			<div className="row justify-content-lg-center">
				{ props.mode == "login" ? <h2>Login</h2> : <h2>Sign up</h2>}
			</div>
			<div className="row justify-content-lg-center text">
				<form onSubmit={formik.handleSubmit}>
					<label htmlFor="login">Login</label><br/>
					<input
						id="login"
						name="login"
						type="text"
						onChange={formik.handleChange}
						value={formik.values.login}
					/><br/>
					<label htmlFor="password">Password</label><br/>
					<input
						id="password"
						name="password"
						type="password"
						onChange={formik.handleChange}
						value={formik.values.password}
					/><br/>
					<div className="row justify-content-lg-center text mt-2">
						<button type="submit">Submit</button>
					</div>
				</form>
			</div>
		</div>
	);
};

export default EntryForm;