import React from "react";

class ReviewTable extends React.Component {
	constructor(props){
		super(props);
		this.state = {
			reviews: []
		}
	}
	
	render(){
		fetch('http://localhost:5000/reviews/').then((res) =>
			res.json().then((data) => {
				let rows = [];
				for (let i = 0; i < data.length; i++) {
					rows.push(
						<tr>
							<td className="review-cell">{ data[i].name }</td>
							<td className="review-cell">{ data[i].comment }</td>
						</tr>
					);
				}
				
				if (rows.length != this.state.reviews.length){
					this.setState({
						reviews: rows
					});
				}
				
			})
		);
		
		return (
			<div className="container">
				<div className="row justify-content-lg-center">
					<div className="col-lg-4">
						<table id="reviews" className="table text">
							<tr>
								<td className="review-cell"><b>Name</b></td>
								<td className="review-cell"><b>Comment</b></td>
							</tr>
							{ this.state.reviews }
						</table>
					</div>
				</div>
			</div>
		);
	}
}

export default ReviewTable;