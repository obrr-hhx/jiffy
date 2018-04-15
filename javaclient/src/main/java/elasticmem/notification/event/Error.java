package elasticmem.notification.event;

import elasticmem.notification.response_type;

public class Error extends Control {

  private String message;

  public Error(String message, response_type type) {
    super(type);
    this.message = message;
  }

  public String getMessage() {
    return message;
  }
}
