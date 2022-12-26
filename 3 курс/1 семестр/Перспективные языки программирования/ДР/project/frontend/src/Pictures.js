import React from "react";

function Pictures() {
	return (
	<div>
		<div className="container">
			<div className="row justify-content-lg-center">
				 <h2>News and events</h2>
			</div>
		</div>
		
		<div className="container">
			<div className="row justify-content-lg-center">
				<div className="col-lg-4">
					 <img src="2.png" className="img-fluid"/>
				</div>
				<div className="col-lg-4">
					 <img src="3.png" className="img-fluid"/>
				</div>
				<div className="col-lg-4">
					 <img src="4.png" className="img-fluid"/>
				</div>
			</div>
			<div className="row justify-content-lg-center">
				<div className="col-lg-4">
					 <img src="1.png" className="img-fluid"/>
				</div>
				<div className="col-lg-4">
					 <img src="5.png" className="img-fluid"/>
				</div>
				<div className="col-lg-4">
					 <img src="6.png" className="img-fluid"/>
				</div>
			</div>
		</div>
	</div>
	);
}

export default Pictures;