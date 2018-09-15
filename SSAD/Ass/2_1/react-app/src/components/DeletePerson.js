import React, { Component } from 'react';
import './DeletePerson.css';

class DeletePerson extends Component {
  constructor() {
    super();
    this.state = {
      data: [],
      formData: {
        id: "",
      },
      submitted: false,
    }
    this.handleSubmit = this.handleSubmit.bind(this);
    this.handleIChange = this.handleIChange.bind(this);
  }

  handleIChange(event) {
    this.state.formData.id = event.target.value;
  }

  // Lifecycle hook, runs after component has mounted onto the DOM structure
  componentDidMount() {
    const request = new Request('http://127.0.0.1:8080/people/');
    fetch(request)
      .then(response => response.json())
        .then(data => this.setState({data: data}));
  }

  handleSubmit (event) {
    event.preventDefault();
    console.log("Entering handleSubmit");
    console.log(JSON.stringify(this.state.formData));
    fetch('http://127.0.0.1:8080/people/'+this.state.formData.id, {
      method: 'delete',
      // body: JSON.stringify(this.state.formData),
   })
      .then(response => {
        if(response.status >= 200 && response.status < 300)
          this.setState({submitted: true});
        console.log(response);
      })
      .then(window.location.reload());
  }

  render() {
    return (
      <div className="App">
        <header className="App-header">
          <h1 className="App-title">Delete a Person</h1>
        </header>

        <form onSubmit={this.handleSubmit}>
          <fieldset>
            <legend> Delete one of the following </legend>
            <table className="table-hover">
              <thead>
                <tr>
                  <th>Select</th>
                  <th>ID</th>
                  <th>First Name</th>
                  <th>Last Name</th>
                  <th>City</th>
                </tr>
              </thead>
              <tbody>{this.state.data.map((item, key) =>
                (
                  <tr key = {key}>
                    <td>
                    <input type="radio" id={item.id}
                    name="drone" value={item.id}
                    onChange={this.handleIChange} />
                    </td>
                    <td>{item.id}</td>
                    <td>{item.firstname}</td>
                    <td>{item.lastname}</td>
                    <td>{item.city}</td>
                  </tr>
                )
              )}
              </tbody>
           </table>
          </fieldset>
          <button type="submit" className="btn btn-default">Submit</button>
        </form>
      </div>
    );
  }
}

export default DeletePerson;
