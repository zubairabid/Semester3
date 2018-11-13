import React, { Component } from 'react';
import './DeleteUser.css';
import Redirect from 'react-router-dom/Redirect';


class DeleteUser extends Component {
  
  constructor() {
    super();
    this.state = {
    username: "",
      data: [],
      submitted: false,
    }
    this.handleSubmit = this.handleSubmit.bind(this);
    this.handleRChange = this.handleRChange.bind(this);
  }


  handleSubmit (event) {
    event.preventDefault();
    fetch('http://localhost:8080/users/'+this.state.username, {
     method: 'DELETE',
   })
      .then(response => {
        if(response.status >= 200 && response.status < 300)
          this.setState({submitted: true});
      })

      this.componentDidMount();
  }

  handleRChange(event) {
    this.state.username = event.target.value;
  }
  
  
  // Lifecycle hook, runs after component has mounted onto the DOM structure
  componentDidMount() {
    const request = new Request('http://localhost:8080/users/');
    fetch(request)
      .then(response => response.json())
        .then(data => this.setState({data: data}));
  }
  

  
  render() {
    
    if(localStorage.getItem("LoggedIn")==="true" &&!(localStorage.getItem("userlogged")==="admin")){
        return(<Redirect to="/" />)
      }

    return (
      <div className="App">
        <header className="App-header">
          <h1 className="App-title">Delete a User</h1>
        </header>
        <div className="formContainer">
          <form onSubmit={this.handleSubmit}>
          { this.state.data.map(function(item, key) {
               return (
                   item.username!="admin"&&
                 <div className='form-group'>
                 <label>
                  <input type='radio' name='delete_radio' key={key} value = {item.username} onClick={this.handleRChange} />
                      {item.name}&nbsp;
                      {item.username}
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

export default DeleteUser;