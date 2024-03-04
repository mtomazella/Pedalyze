import { IconProp } from '@fortawesome/fontawesome-svg-core'
import {
  faBattery,
  faBolt,
  faClock,
  faCrosshairs,
  faFan,
  faPlug,
  faTemperature3,
  faWaveSquare,
} from '@fortawesome/free-solid-svg-icons'
import { Metrics, MetricsField, MetricsFieldData } from 'src/hooks'

export const formatMeasurements = (currentMetrics: Metrics) => {
  const infoToAddAndOrder: Record<MetricsField, { icon: any }> = {
    tension: {
      icon: faBolt,
    },
    actual_current: {
      icon: faBattery,
    },
    target_current: {
      icon: faCrosshairs,
    },
    power: {
      icon: faPlug,
    },
    temperature: {
      icon: faTemperature3,
    },
    fan_percentage: {
      icon: faFan,
    },
    routine_time: {
      icon: faClock,
    },
    duty_cycle: {
      icon: faWaveSquare,
    },
  }
  const result: Partial<
    Record<MetricsField, MetricsFieldData & { icon: any }>
  > = {}
  Object.keys(infoToAddAndOrder).forEach((field: string) => {
    if (!currentMetrics[field as MetricsField]) return
    result[field as MetricsField] = {
      ...currentMetrics[field as MetricsField],
      ...infoToAddAndOrder[field as MetricsField],
    }
  })
  return Object.values(result) as (MetricsFieldData & { icon: IconProp })[]
}
