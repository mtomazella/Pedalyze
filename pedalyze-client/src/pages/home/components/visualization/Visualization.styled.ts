import styled, { css } from 'styled-components'

const inputItem = ({
  background,
  border,
  emptyBackground,
}: Record<string, string>) => css`
  display: flex;
  justify-content: center;
  align-items: center;
  /* max-width: 5rem; */
  aspect-ratio: 1;
  width: 100%;
  border: 2px solid ${border};
  border-radius: 8px;
  background-color: ${background};

  > h3 {
    margin: 0;
    color: ${border};
    font-size: 3rem;
  }

  &:hover {
    background-color: color-mix(in srgb, ${border} 50%, ${background} 50%);
  }

  &.selected {
    background-color: ${border};

    > h3 {
      color: ${background};
    }
  }
  &.empty {
    background-color: ${emptyBackground};
  }
`

export const StyledVisualization = styled.section`
  ${({ theme }) => css`
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
    height: 100%;
    width: 100%;

    > div {
      display: flex;
      flex-direction: column;
      justify-content: center;
      align-items: center;
      height: 100%;
      width: 100%;
      max-width: 40rem;

      > h1 {
        font-size: 2rem;
        color: ${theme.home.titles};
        align-self: flex-start;
      }

      > div.buttons {
        display: grid;
        grid-template-columns: repeat(4, 1fr);
        grid-gap: 1rem;
        width: 100%;
        margin-bottom: 2rem;

        > div {
          display: flex;
          justify-content: center;
          align-items: center;
          aspect-ratio: 1;

          > button {
            ${inputItem(theme.home.visualization.buttons)}
          }
        }
      }

      > div.channels {
        display: grid;
        grid-template-columns: repeat(5, 1fr);
        grid-gap: 1rem;
        width: 100%;

        > div {
          display: flex;
          justify-content: center;
          align-items: center;
          aspect-ratio: 1;

          > button {
            ${inputItem(theme.home.visualization.channels)}
            border-radius: 50%;
          }
        }
      }
    }
  `}
`
