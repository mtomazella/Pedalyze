import React from 'react'
import { StyledVisualization } from './Visualization.styled'
import {
  PedalyzeButton,
  PedalyzeChannel,
  PedalyzeInputType,
  PedalyzePreset,
} from '../../../../hooks'
import { InputSelection } from '../../index'

const Button: React.FC<
  PedalyzeButton & {
    selected: boolean
    onClick: (value: InputSelection | null) => void
  }
> = ({ id, selected, onClick }) => {
  return (
    <div className="button">
      <button
        className={selected ? 'selected' : ''}
        onClick={() => onClick(selected ? null : { type: 'button', id })}
      >
        <h3 className="orbitron">{id}</h3>
      </button>
    </div>
  )
}

const Channel: React.FC<
  PedalyzeButton & {
    selected: boolean
    onClick: (value: InputSelection | null) => void
  }
> = ({ id, selected, onClick }) => {
  return (
    <div className="channel">
      <button
        className={selected ? 'selected' : ''}
        onClick={() => onClick(selected ? null : { type: 'channel', id })}
      >
        <h3 className="orbitron">{id}</h3>
      </button>
    </div>
  )
}

export const Visualization: React.FC<{
  preset: PedalyzePreset
  selected: { type: PedalyzeInputType; id: number } | null
  setSelected: (
    selected: { type: PedalyzeInputType; id: number } | null
  ) => void
}> = ({ preset, selected = null, setSelected }) => {
  return (
    <StyledVisualization>
      <div>
        <h1>Botões</h1>
        <div className="buttons">
          {preset.buttons.map(button => (
            <Button
              key={button.id}
              {...button}
              selected={
                !!selected &&
                button.id === selected.id &&
                selected.type === 'button'
              }
              onClick={setSelected}
            />
          ))}
        </div>

        <h1>Canais</h1>
        <div className="channels">
          {preset.channels.map(channel => (
            <Channel
              key={channel.id}
              {...channel}
              selected={
                !!selected &&
                channel.id === selected.id &&
                selected.type === 'channel'
              }
              onClick={setSelected}
            />
          ))}
        </div>
      </div>
    </StyledVisualization>
  )
}
