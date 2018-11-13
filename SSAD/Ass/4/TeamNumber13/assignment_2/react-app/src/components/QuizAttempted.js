import React, { Component } from 'react';
import Redirect from 'react-router-dom/Redirect';

class QuizAttempted extends Component {
    constructor() {
        super();
        this.state = {        
            data: [],
            submitted: false,
            mounted: false,
        }
        
}
componentDidMount() {
  this.state.mounted=true
  const request = new Request('http://localhost:8080/quizscore/'+localStorage.userlogged);
  fetch(request)
    .then(response => response.json())
      .then(data => this.setState({data: data}));

}


  render() {


    if(localStorage.getItem("LoggedIn")==="false"){
      return(<Redirect to="/" />)
    }

    console.log(this.state.data)
    return (
      <div className="App">
        <header className="App-header">
          <h1 className="App-title">Quizzes Attempted</h1>
        </header>
        <ol>
        {this.state.data.map(function(item,key){
          return(
            <li>QuizId: {item.QuizId} Score:{item.Score}</li>
          )

        },this)
      }
        </ol>

      </div>
    );
  
    }
}

export default QuizAttempted;