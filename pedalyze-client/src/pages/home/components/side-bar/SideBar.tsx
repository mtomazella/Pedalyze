import React from 'react'

import {
  faArrowRight,
  faBoxArchive,
  faGear,
  faSave,
} from '@fortawesome/free-solid-svg-icons'
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome'
import { IconButton, Tooltip } from '@mui/material'

import { StyledPanel, StyledSideBar } from './SideBar.styled'
import { PedalyzePreset } from 'src/hooks'
import { LockedInput } from './../../../../components'

type ButtonKey = 'upload' | 'save' | 'archive' | 'config'

export const SideBar: React.FC<{
  preset: PedalyzePreset
  buttonHandlers: Partial<
    Record<
      ButtonKey,
      {
        onClick?: () => void
      }
    >
  >
}> = ({ buttonHandlers }) => (
  <StyledSideBar>
    <StyledPanel>
      <Tooltip title="Enviar para a carga">
        <IconButton onClick={buttonHandlers.upload?.onClick}>
          <FontAwesomeIcon icon={faArrowRight} />
        </IconButton>
      </Tooltip>

      <Tooltip title="Salvar configurações">
        <IconButton onClick={buttonHandlers.save?.onClick}>
          <FontAwesomeIcon icon={faSave} />
        </IconButton>
      </Tooltip>

      <Tooltip title="Ver configurações salvas">
        <IconButton onClick={buttonHandlers.archive?.onClick}>
          <FontAwesomeIcon icon={faBoxArchive} />
        </IconButton>
      </Tooltip>

      <Tooltip title="Configurações da aplicação">
        <IconButton onClick={buttonHandlers.config?.onClick}>
          <FontAwesomeIcon icon={faGear} />
        </IconButton>
      </Tooltip>
    </StyledPanel>

    <LockedInput label="Nome da configuração" value="test" />
  </StyledSideBar>
)
