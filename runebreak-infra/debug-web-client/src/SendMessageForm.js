import PropTypes from 'prop-types';
import React from 'react';

class SendMessageForm extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      recipientId: '',
      text: '',
      token: '',
    };

    this.handleTextFieldChange = this.handleTextFieldChange.bind(this);
  }
  
  onSubmit = (event) => {
    event.preventDefault()
    this.props.onSubmit(this.state.recipientId, this.state.text, this.state.token);
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
          Recipient Id:
          <input
            name="recipientId"
            type="text"
            value={this.state.recipientId}
            onChange={this.handleTextFieldChange} />
        </label>
        <br/>
        <label>
          Message Text:
          <input
            name="text"
            type="text"
            value={this.state.text}
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

SendMessageForm.propTypes = {
    onSubmit: PropTypes.func.isRequired,
}

export default SendMessageForm;