export type PedalyzeInputType = 'button' | 'channel'

export type PedalyzeCommand = {
  command: string
  channel: number
  note: number
  velocity: number
}

export type PedalyzeCondition = {
  conditions: {
    type: PedalyzeInputType
    id: number
    operand: 'eq' | 'ne' | 'gt' | 'lt' | 'gte' | 'lte'
    value: number
  }[]
  commands: PedalyzeCommand[]
}

export type PedalyzeButton = {
  id: number
  commands: PedalyzeCommand[]
  conditions: PedalyzeCondition[]
}

export type PedalyzeChannel = {
  id: number
  commands: PedalyzeCommand[]
  conditions: PedalyzeCondition[]
}

export type PedalyzePreset = {
  name: string
  buttons: PedalyzeButton[]
  channels: PedalyzeChannel[]
}
