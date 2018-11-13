import React, { Component } from 'react';
import Redirect from 'react-router-dom/Redirect';

class Quizzes extends Component {
    constructor() {
        super();
        this.state = {        
            quizzes: [],
            submitted: false,
            mounted: false,
        }
        this.handlequiz=this.handlequiz.bind(this)
        
}
componentDidMount() {
  this.state.mounted=true
  const request = new Request('http://127.0.0.1:8080/quizzes/');
  fetch(request)
    .then(response => response.json())
      .then(data => this.setState({quizzes: data}));

}


handlequiz(event){
  localStorage.setItem("quiz_id",event.target.getAttribute('data-qid'))
  window.location.href = "http://localhost:3000/Quiz"
}

  render() {


    if(localStorage.getItem("LoggedIn")==="false"){
      return(<Redirect to="/" />)
    }

    console.log(this.state.quizzes)
    return (
      <div className="App">
        <header className="App-header">
          <h1 className="App-title">Quizzes</h1>
        </header>
        <ol>
        {this.state.quizzes.map(function(item,key){
          return(
            <li><button type="button" data-qid={item.id} onClick={this.handlequiz}>GO</button>QuizId: {item.id} Quiz Genre: {item.genre}</li>
          )

        },this)
      }
        </ol>

      </div>
    );
  
    }
}

export default Quizzes;