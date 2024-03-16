import {
  FormControl,
  IconButton,
  InputAdornment,
  InputLabel,
  OutlinedInput,
  TextField,
} from '@mui/material'
import { Edit } from '@mui/icons-material'
import React, { useCallback, useRef, useState } from 'react'
import styled from 'styled-components'

const StyledLockedInput = styled.div`
  display: flex;
  flex-direction: row;
  align-items: center;

  > * {
    pointer-events: none;
  }

  button {
    pointer-events: all;
  }
`

export const LockedInput: React.FC<{
  label: string
  value: string
  setValue?: (value: string) => void
}> = ({ label, value = '', setValue }) => {
  const ref = useRef<HTMLInputElement>()

  const focusInput = useCallback(() => {
    ref?.current?.focus()
  }, [ref])

  return (
    <StyledLockedInput>
      <FormControl sx={{ width: '100%' }} variant="outlined">
        <InputLabel htmlFor="outlined-adornment-password"></InputLabel>
        <OutlinedInput
          id="outlined-adornment-password"
          inputRef={ref}
          endAdornment={
            <InputAdornment position="end">
              <IconButton
                aria-label="toggle password visibility"
                onClick={focusInput}
                edge="end"
              >
                <Edit />
              </IconButton>
            </InputAdornment>
          }
          label="Password"
        />
      </FormControl>
    </StyledLockedInput>
  )
}
