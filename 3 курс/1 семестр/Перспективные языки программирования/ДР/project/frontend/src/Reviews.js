import React from "react";
import { useFormik } from "formik";
import ReviewTable from './ReviewTable';

const Reviews = () => {
	const refTable = React.useRef(null);
	
	const formik = useFormik({
		initialValues: { name: "", comment: "" },
		onSubmit: async values => {
			let formData = new FormData();
			formData.append('name', JSON.parse(window.localStorage.getItem('nickname')));
			formData.append('comment', values['comment']);
			
			let response = await fetch('http://localhost:5000/reviews/', {
				method: 'POST',
				body: formData
			});

			refTable.current.forceUpdate();
		}
	});

	return (
		<div>
			<div className="container">
				<div className="row justify-content-lg-center">
					<h2>Reviews</h2>
				</div>
            </div>
			<ReviewTable />
			<div className="container">
				<div className="row justify-content-lg-center text">
					{ window.localStorage.getItem('nickname') == JSON.stringify("") ? 
						<h2>Login to send review</h2>
					:
						<form onSubmit={formik.handleSubmit}>
							<label htmlFor="comment">Comment</label><br/>
							<input
								id="comment"
								name="comment"
								type="text"
								onChange={formik.handleChange}
								value={formik.values.comment}
							/><br/>
							<div className="row justify-content-lg-center text mt-2">
								<button type="submit">Submit</button>
							</div>
						</form>
					}
				</div>
			</div>
		</div>
	);
};

export default Reviews;