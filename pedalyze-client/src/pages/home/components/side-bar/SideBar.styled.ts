import { Card } from '@mui/material'
import styled, { css } from 'styled-components'

export const StyledSideBar = styled.div`
  display: flex;
  flex-direction: column;
  gap: 0.5rem;
  padding: 1rem 1rem 1rem 0;
  width: 100%;
`

export const StyledPanel = styled(Card)`
  ${({ theme }) => css`
    display: flex;
    flex-direction: row;
    align-items: center;
    flex-wrap: wrap;
    justify-content: space-around;
    font-family: monospace;
    color: gray;
    font-size: 1.5rem;
    padding: 0.8rem;
    width: 100%;
    max-width: 30rem;
    align-self: flex-end;
    background-color: ${theme.background};
    border: 1px solid ${theme.home.sideBar.border};

    > .MuiIconButton-root {
      color: white;
      aspect-ratio: 1;
      width: fit-content;
      padding: 0.5rem;
      margin: 0.5rem;
      align-self: center;
      justify-self: center;

      &:nth-of-type(1) {
        background-color: #82d582;
      }
      &:nth-of-type(2) {
        background-color: #6363c2;
      }
      &:nth-of-type(3) {
        background-color: #bb5dbb;
      }
      &:nth-of-type(4) {
        background-color: #ffbf47;
      }
    }
  `}
`
