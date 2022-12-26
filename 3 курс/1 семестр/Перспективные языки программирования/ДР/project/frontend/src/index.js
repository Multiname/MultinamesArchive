import React from 'react';
import ReactDOM from 'react-dom/client';
import Main from './Main';
import Entry from './Entry';
import reportWebVitals from './reportWebVitals';
import { BrowserRouter as Router, Routes, Route } from 'react-router-dom';

const root = ReactDOM.createRoot(document.getElementById('root'));
root.render(
	<Router>
		<div>
		  <Routes>
			<Route path="*" element={<Main />} />
			<Route path="/LogIn" element={<Entry mode="login" />} />
			<Route path="/SignUp" element={<Entry mode="signup" />} />
		   </Routes>
		</div>
	</Router>
);

reportWebVitals();