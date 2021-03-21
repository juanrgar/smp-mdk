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

#ifndef MDK_MODEL_H_
#define MDK_MODEL_H_

#include "Mdk/Component.h"
#include "Smp/IModel.h"

namespace Smp {
namespace Mdk {
class Model
  : public Smp::Mdk::Component
  , public virtual Smp::IModel
{
public:
  Model(void);
  Model(Smp::String8 name,
        Smp::String8 description,
        Smp::IComposite* parent) throw(Smp::InvalidObjectName);
  virtual ~Model(void);

  Smp::ModelStateKind GetState(void) const;
  void Publish(Smp::IPublication* receiver) throw(
    Smp::IModel::InvalidModelState);
  void Configure(Smp::Services::ILogger* logger) throw(
    Smp::IModel::InvalidModelState);
  void Connect(Smp::ISimulator* simulator) throw(
    Smp::IModel::InvalidModelState);

protected:
  Smp::IService* GetService(const Smp::String8 serviceName) const;

  Smp::ModelStateKind m_state;
  Smp::ISimulator* m_simulator;
  Smp::IPublication* m_publication;

private:
  void CheckState(Smp::ModelStateKind exp);

  Smp::Services::ILogger* m_logger;
};
} // namespace Mdk
} // namespace Smp

#endif // MDK_MODEL_H_
