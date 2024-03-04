import React, { useCallback, useState } from 'react'
import { Panel, PanelGroup, PanelResizeHandle } from 'react-resizable-panels'

import styled from 'styled-components'

import { Page } from '../../blocks/page'
import {
  PedalyzeInputType,
  PedalyzePreset,
  useConfig,
  usePresets,
} from '../../hooks'
import { SideBar } from './components/side-bar/SideBar'
import { Visualization } from './components/visualization/Visualization'

export type InputSelection = { type: PedalyzeInputType; id: number }

const StyledHome = styled(Page)`
  display: flex;
  flex-direction: row;
  background-color: ${({ theme }) => theme.background};

  > div {
    > .resize {
      width: 5px;
      background-color: lightgray;
      opacity: 0;
      margin: 0 0.5rem;

      transition-duration: 0.5s;
    }
    > .resize:hover {
      opacity: 1;
    }
  }
`

export const Home = () => {
  const routineApi = usePresets()
  const configApi = useConfig()

  const [preset, setPreset] = useState<PedalyzePreset>({
    name: '',
    buttons: Array(12)
      .fill(0)
      .map((_, i) => ({
        id: i + 1,
        commands: [
          {
            command: 'note_on',
            channel: 0,
            note: Math.floor(Math.random() * 127),
            velocity: 127,
          },
        ],
        conditions: [],
      })),
    channels: Array(5)
      .fill(0)
      .map((_, i) => ({
        id: i + 1,
        commands: [
          {
            command: 'note_on',
            channel: 0,
            note: Math.floor(Math.random() * 127),
            velocity: 127,
          },
        ],
        conditions: [],
      })),
  })
  const [selectedInput, setSelectedInput] = useState<InputSelection | null>(
    null
  )

  const onUpload = useCallback(() => {
    routineApi.upload(preset)
  }, [preset, routineApi.upload])

  const onSave = useCallback(() => {
    routineApi.save(preset)
  }, [preset, routineApi.save])

  const onConfig = useCallback(() => {
    configApi.fetch()
  }, [configApi.fetch])

  return (
    <StyledHome>
      <PanelGroup direction="horizontal">
        <Panel>
          <Visualization
            preset={preset}
            selected={selectedInput}
            setSelected={setSelectedInput}
          />
        </Panel>

        <PanelResizeHandle className="resize" />

        <Panel defaultSize={60}>
          <SideBar
            buttonHandlers={{
              upload: { onClick: onUpload },
              save: { onClick: onSave },
              config: { onClick: onConfig },
            }}
          />
        </Panel>
      </PanelGroup>
    </StyledHome>
  )
}
