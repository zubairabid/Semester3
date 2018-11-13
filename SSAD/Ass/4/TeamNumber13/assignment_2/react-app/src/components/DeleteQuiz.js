import React, { Component } from 'react';
import Redirect from 'react-router-dom/Redirect';

class DeleteQuiz extends Component {
    constructor() {
        super();
        this.state = {
        
            id: null,
            quizzes: [],
            submitted: false,
            mounted: false,
        }
        this.handleRChange=this.handleRChange.bind(this)
        this.handleSubmit=this.handleSubmit.bind(this)
}

componentDidMount() {
  this.state.mounted=true
  const request = new Request('http://localhost:8080/quizzes/');
  fetch(request)
    .then(response => response.json())
      .then(data => this.setState({quizzes: data}));

}
handleRChange(event) {
    this.state.id = event.target.value;
  }

handleSubmit (event) {
    event.preventDefault();
    fetch('http://localhost:8080/quizzes/'+this.state.id, {
     method: 'DELETE',
   })
      .then(response => {
        if(response.status >= 200 && response.status < 300)
          this.setState({submitted: true});
      })

      this.componentDidMount();
  }

  render() {

    if(localStorage.getItem("LoggedIn")==="true" &&!(localStorage.getItem("userlogged")==="admin")){
        return(<Redirect to="/" />)
      }

    if(localStorage.getItem("LoggedIn")==="false"){
      return(<Redirect to="/" />)
    }

    console.log(this.state.quizzes)
    return (
        <div className="App">
          <header className="App-header">
            <h1 className="App-title">Delete a Quiz</h1>
          </header>
          <div className="formContainer">
            <form onSubmit={this.handleSubmit}>
            { this.state.quizzes.map(function(item, key) {
                 return (
                   <div className='form-group'>
                   <label>
                    <input type='radio' name='delete_radio' key={key} value = {item.id} onClick={this.handleRChange} />
                        Genre: {item.genre}&nbsp;
                        Quiz id: {item.id}
                    </label>
                    </div>
                  )
               }, this)}
             
                  <button type="submit" className="btn btn-default">Submit</button>
            </form>
          </div>
  
        </div>
      );
  
    }
}

export default DeleteQuiz;