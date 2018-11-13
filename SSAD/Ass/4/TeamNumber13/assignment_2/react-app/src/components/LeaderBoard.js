import React, { Component } from 'react';
import Redirect from 'react-router-dom/Redirect';

class LeaderBoard extends Component {
    constructor() {
        super();
        this.state = {
            genre: "all",
            data: [],
            submitted: false,
            mounted: false,
        }
        this.handleGchange = this.handleGchange.bind(this)
        
}
componentDidMount() {
  this.state.mounted=true

      const request = new Request('http://localhost:8080/leaderboard/',{
        method: 'POST',
        body: JSON.stringify({genre:this.state.genre}),
    });
    fetch(request)
      .then(response => response.json())
        .then(data => this.setState({data: data}));


}

handleGchange(event){
    this.setState({genre: event.target.value})
}

    render() {

    if(localStorage.getItem("LoggedIn")==="false"){
      return(<Redirect to="/" />)
    }
    var set1 = new Set(), i = 0, len = this.state.data.length;
    for (let i = 0; i < len; i++) {
        set1.add(this.state.data[i].Genre);
    }
    

    var arr = Array.from(set1)
    
    console.log(this.state.data)
    return (
      <div className="App">
        <header className="App-header">
          <h1 className="App-title">LeaderBoard</h1>
        </header>
        <select name="genre">
        <option value="all" onClick={this.handleGchange}>All</option>
        {arr.map(function(item, key) {
               return (
                <option value={item} onClick={this.handleGchange}>{item}</option>
                )
             },this)}

        </select>
        
        
        <table className="table-hover">
          <thead>
            <tr>
              <th>Username</th>
              <th>Genre</th>
              <th>Score</th>
            </tr>
          </thead>
          <tbody>{this.state.data.map(function(item, key) {
               return (
                    (item.Genre==this.state.genre || this.state.genre=="all")&&
                  <tr key = {key}>
                      <td>{item.Username}</td>
                      <td>{item.Genre}</td>
                      <td>{item.Score}</td>
                  </tr>
                )
             },this)}
          </tbody>
       </table>

      </div>
    );
  
    }
}

export default LeaderBoard;