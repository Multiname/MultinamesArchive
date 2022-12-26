import React, { useState, useEffect } from "react";

function Navbar() {
	const [nickname, setNickname] = useState("");
	
	useEffect(() => {
		const data = window.localStorage.getItem('nickname');
		if ( data !== JSON.stringify("") ) setNickname(JSON.parse(data));
	}, []);
	
	const Quit = () => {
		window.localStorage.setItem('nickname', JSON.stringify(""));
		setNickname("");
		window.location = '/main';
	}
	
	return (
		<nav className="navbar fixed-top navbar-expand-lg navbar-dark bg-dark">
			<a className="navbar-brand" href="/">Fitness center Lifeform</a>
			
			<div className="collapse navbar-collapse d-flex justify-content-end">
				<ul className="navbar-nav">
					<li className="nav-item active">
					    { nickname == "" ? <a className="nav-link" href="/SignUp">Sign up</a> : <div className="nav-link">{ nickname }</div>}
					</li>
					<li className="nav-item active">
						{ nickname == "" ? <a className="nav-link" href="/LogIn">Login</a> : <button type="button" className="nav-link btn btn-link" onClick={ Quit }>Quit</button>}
					</li>
				</ul>
			</div>
		</nav>
	);
}

export default Navbar;