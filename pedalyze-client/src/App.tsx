import React from 'react'

import { Home } from './pages'
import { ThemeProvider, createGlobalStyle } from 'styled-components'
import { themes } from './themes'

const App: React.FC = () => {
  const theme = themes['vibrantLight']

  const GlobalStyle = createGlobalStyle`
    body {
      background-color: ${theme.background};
    }
  `

  return (
    <ThemeProvider theme={theme}>
      <GlobalStyle />
      <Home />
    </ThemeProvider>
  )
}

export default App
