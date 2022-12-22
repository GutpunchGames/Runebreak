import PropTypes from 'prop-types';
import React from 'react';

class AttemptConnectForm extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      userId: '',
      token: '',
    };

    this.handleTextFieldChange = this.handleTextFieldChange.bind(this);
  }
  
  onSubmit = (event) => {
    event.preventDefault()
    this.props.onSubmit(this.state.userId, this.state.token);
    return false;
  };

  handleTextFieldChange(event) {
    const target = event.target;
    const name = target.name;
    const value = target.value;

    this.setState({
      [name]: value
    });
  }

  render() {
    return (
      <form onSubmit={this.onSubmit}>
        <label>
          User Id:
          <input
            name="userId"
            type="text"
            value={this.state.userId}
            onChange={this.handleTextFieldChange} />
        </label>
        <br/>
        <label>
          Token:
          <input
            name="token"
            type="text"
            value={this.state.token}
            onChange={this.handleTextFieldChange} />
        </label>
        <br/>
        <input type="submit" value="Submit"/>
      </form>
    );
  }
}

AttemptConnectForm.propTypes = {
    onSubmit: PropTypes.func.isRequired,
}

export default AttemptConnectForm;