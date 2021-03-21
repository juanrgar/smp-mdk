/** This file is part of smp-mdk
 *
 * Copyright (C) 2018 Juan R. Garcia Blanco
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Mdk/Model.h"

#include "Smp/ISimulator.h"

using namespace Smp::Mdk;

Model::Model(void)
  : m_state(Smp::MSK_Created)
  , m_simulator(NULL)
  , m_publication(NULL)
{}

Model::Model(Smp::String8 name,
             Smp::String8 description,
             Smp::IComposite* parent) throw(Smp::InvalidObjectName)
  : Component(name, description, parent)
  , m_state(Smp::MSK_Created)
  , m_simulator(NULL)
  , m_publication(NULL)
{}

Model::~Model(void) {}

Smp::ModelStateKind
Model::GetState(void) const
{
  return this->m_state;
}

void
Model::Publish(Smp::IPublication* receiver) throw(
  Smp::IModel::InvalidModelState)
{
  CheckState(Smp::MSK_Created);

  this->m_state = MSK_Publishing;

  this->m_publication = receiver;
}

void
Model::Configure(Smp::Services::ILogger* logger) throw(
  Smp::IModel::InvalidModelState)
{
  CheckState(Smp::MSK_Publishing);

  this->m_state = MSK_Configured;

  this->m_logger = logger;
}

void
Model::Connect(Smp::ISimulator* simulator) throw(Smp::IModel::InvalidModelState)
{
  CheckState(Smp::MSK_Configured);

  this->m_state = MSK_Connected;

  this->m_simulator = simulator;
}

Smp::IService*
Model::GetService(const Smp::String8 serviceName) const
{
  if (serviceName == NULL) {
    return NULL;
  }

  if (this->m_simulator == NULL) {
    return NULL;
  }

  return this->m_simulator->GetService(serviceName);
}

void
Model::CheckState(Smp::ModelStateKind exp)
{
  if (this->m_state != exp) {
    throw Smp::IModel::InvalidModelState(this->m_state, exp);
  }
}
