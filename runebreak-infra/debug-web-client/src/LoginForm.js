import PropTypes from 'prop-types';
import React from 'react';

class LoginForm extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      username: '',
      password: ''
    };

    this.handleTextFieldChange = this.handleTextFieldChange.bind(this);
  }
  
  onSubmit = (event) => {
    event.preventDefault()
    this.props.onSubmit(this.state.username, this.state.password);
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
    const {usernameLabel, passwordLabel} = this.props;

    return (
      <form onSubmit={this.onSubmit}>
        <label>
          {usernameLabel}:
          <input
            name="username"
            type="text"
            value={this.state.username}
            onChange={this.handleTextFieldChange} />
        </label>
        <br />
        <label>
          {passwordLabel}:
          <input
            name="password"
            type="text"
            value={this.state.password}
            onChange={this.handleTextFieldChange} />
        </label>
        <br/>
        <input type="submit" value="Submit"/>
      </form>
    );
  }
}

LoginForm.propTypes = {
    usernameLabel: PropTypes.string.isRequired,
    passwordLabel: PropTypes.string.isRequired,
    onSubmit: PropTypes.func.isRequired,
}

export default LoginForm;