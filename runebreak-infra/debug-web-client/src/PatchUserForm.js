import PropTypes from 'prop-types';
import React from 'react';

class PatchUserForm extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      username: '',
      userId: '',
      token: ''
    };

    this.handleTextFieldChange = this.handleTextFieldChange.bind(this);
  }
  
  onSubmit = (event) => {
    event.preventDefault()
    this.props.onSubmit(this.state.username, this.state.userId, this.state.token);
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
    const {usernameLabel, userIdLabel, tokenLabel} = this.props;

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
          {userIdLabel}:
          <input
            name="userId"
            type="text"
            value={this.state.userId}
            onChange={this.handleTextFieldChange} />
        </label>
        <br/>
        <label>
          {tokenLabel}:
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

PatchUserForm.propTypes = {
    usernameLabel: PropTypes.string.isRequired,
    userIdLabel: PropTypes.string.isRequired,
    tokenLabel: PropTypes.string.isRequired,
    onSubmit: PropTypes.func.isRequired,
}

export default PatchUserForm;