type supportedLanguage =
  | English
  | Nederlands;

type state = {current: supportedLanguage};

type action =
  | ChangeLanguage(supportedLanguage);

let initialState = () => {current: English};

let reducer = (action, _state) =>
  switch action {
  | ChangeLanguage(language) => {current: language}
  };
