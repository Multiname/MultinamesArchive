import React from "react";
import Navbar from './Navbar';
import EntryForm from './EntryForm';

function Entry(props) {
	return (
	<div>
		<Navbar />
		<EntryForm mode={props.mode} />
	</div>
	);
}

export default Entry;